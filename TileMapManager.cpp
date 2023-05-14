#include "stdafx.h"

TileMapManager::TileMapManager(GLuint mapDataCount, GLuint pageTiles, GLuint *mapData, GLuint viewportw, GLuint viewporth, GLuint tilewidth, GLuint tileheight, GLuint tileseparation, GLuint tileframetime, GLuint program, GLenum mode)
{
	ptrvPosLayout = nullptr;
	ptrvTexLayout = nullptr;
	ptrvColLayout = nullptr;
	ptrvTraLayout = nullptr;
	ptrvScaLayout = nullptr;
	ptrvRotLayout = nullptr;
	ptrVertexBuffer = nullptr;
	ptrVertexArray = nullptr;
	ptrIndexBuffer = nullptr;

	batchDrawCount = 0;
	batchDrawCalls = 0;
	textureCounter = 0;
	offsetX = 0;
	offsetY = 0;
	speedX = 0;
	speedY = 0;
	actualPage = 0;
	mapPageCount = 0;
	pageTileCount = 0;
	actualPage = 0;
	mainPage = true;
	drawingMode = GL_TRIANGLES;
	vertexBufferStrideCount = 20;
	quadFloatCount = 80;
	programID = program;
	tileWidth = tilewidth;
	tileHeight = tileheight;
	tileSeparation = tileseparation;
	tileFrameTime = tileframetime;
	viewPortW = viewportw;
	viewPortH = viewporth;
	drawingMode = mode;
	maxTextureUnits = 0;
	frameCounter = 0;

	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	batchDrawOffset = maxTextureUnits;
	pageTileCount = pageTiles;
	mapPageCount = mapDataCount / pageTileCount;

	mapTilesArray = vector<Sprite *>(mapDataCount);
	tilesArray = vector<Sprite *>( pageTileCount * 4);
	vertexArray = vector<float>(tilesArray.size() * vertexBufferStrideCount * 4);

	vector<Sprite *>::iterator mtit;
	vector<Sprite *>::iterator tait;
	vector<float >::iterator vait;

	char palette = 0x00;
	char page = 0x00;
	short tileColumn = 0x0000;
   short tileRow = 0x0000;
	char tileFrames = 0x00;
	char collisionData = 0x00;

	//Init all the tiles from the array of data

	if (mapTilesArray.size() > 0)
	{
		uint i = 0;

		for (mtit = mapTilesArray.begin(); mtit != mapTilesArray.end(); mtit++)
		{
			palette = 		((mapData[i] & 0xF0000000) >> 28);
			page = 			((mapData[i] & 0x0F000000) >> 24);
			tileColumn = 	((mapData[i] & 0x00FF0000) >> 16);
			tileRow = 		((mapData[i] & 0x0000FF00) >> 8);
			tileFrames = 	((mapData[i] & 0x000000F0) >> 4);
			collisionData = ((mapData[i] & 0x0000000F)     );

			(*mtit) = new Sprite(palette, page);
			(*mtit)->tilePosition.x = tileColumn;
			(*mtit)->tilePosition.y = tileRow;
         (*mtit)->collisionData = collisionData;


			if(tileFrames > 0)
			{
            (*mtit)->ptrAnimation = new Animation(0,tileFrames,0,tileFrameTime,Animation::LOOP_FORWARD);
         }

         i++;
      }
	}

	//Init 4 pages of tiles for copy to vertex buffer
	if (tilesArray.size() > 0)
	{
		for (tait = tilesArray.begin(); tait != tilesArray.end(); tait++)
		{
			(*tait) = new Sprite();
			(*tait)->tileDimension.x = tileWidth;
			(*tait)->tileDimension.y = tileHeight;
      }
	}

	//Create data array for updates
	if (vertexArray.size() > 0)
	{
		for (vait = vertexArray.begin(); vait != vertexArray.end(); vait++)
			(*vait) = 0.0f;
	}

	initBuffers();
	initLayouts();
	updateEnitities();
}

TileMapManager::~TileMapManager()
{

	delete ptrVertexBuffer;
	delete ptrVertexArray;
	delete ptrIndexBuffer;
	delete ptrvPosLayout;
	delete ptrvTexLayout;
	delete ptrvColLayout;
	delete ptrvTraLayout;
	delete ptrvScaLayout;
	delete ptrvRotLayout;
}

void TileMapManager::initBuffers()
{
	//Vertex Array//
	ptrVertexArray = new VertexArray();

	//Vertex Buffer//
	ptrVertexBuffer = new VertexBuffer(vertexArray.size(), sizeof(GLfloat), vertexArray.data());

	//Index Buffer//
	ptrIndexBuffer = new IndexBuffer(6 * pageTileCount * 4, sizeof(GL_UNSIGNED_INT), nullptr);

	batchDrawCalls = ptrIndexBuffer->bufferCount / batchDrawOffset;
}

void TileMapManager::initLayouts()
{
	/*
	DATA BUFFER:
	Entity 0
		Sprite 0 [XYZ-STPQ-RGBA-TTT-SSS-RRR] , [XYZ-STRQ-RGBA-TTT-SSS-RRR] , [XYZ-STRQ-RGBA-TTT-SSS-RRR] , [XYZ-STRQ-RGBA-TTT-SSS-RRR] = 20  Floats
		20 Float * 4 Vertices = 80 Floats
		1 Quad = 80 Floats
	*/
	ptrvPosLayout = new VertexBufferLayout(programID, "vPos", 3, GL_FALSE, 20, 0 * 4);
	ptrvTexLayout = new VertexBufferLayout(programID, "vTex", 4, GL_FALSE, 20, 3 * 4);
	ptrvColLayout = new VertexBufferLayout(programID, "vCol", 4, GL_FALSE, 20, 7 * 4);
	ptrvTraLayout = new VertexBufferLayout(programID, "vTra", 3, GL_FALSE, 20, 11 * 4);
	ptrvScaLayout = new VertexBufferLayout(programID, "vSca", 3, GL_FALSE, 20, 14 * 4);
	ptrvRotLayout = new VertexBufferLayout(programID, "vRot", 3, GL_FALSE, 20, 17 * 4);

	ptrVertexArray->detach();
	ptrVertexBuffer->detach();
	ptrIndexBuffer->detach();
}

void TileMapManager::update()
{
	offsetX = offsetX + speedX;
	offsetY = offsetY + speedY;

	updateEnitities();
	updateVertexBuffer();
}

void TileMapManager::loadTile()
{

}

void TileMapManager::loadPage(GLfloat tileDestinationX, GLfloat tileDestinationY, GLuint pageSource, GLuint pageDestination)
{
	uint tw = viewPortW / tileWidth;
	uint th = viewPortH / tileHeight;

	uint w = 0;
	uint h = th - 1;

	for (uint i = 0 ; i < pageTileCount; i++)
	{
		tilesArray[i + (pageTileCount * pageDestination)] = mapTilesArray[i +( pageTileCount * pageSource)];
		tilesArray[i + (pageTileCount * pageDestination)]->transformation.translate.x = (w * tileWidth) + (tileDestinationX * tileWidth);
		tilesArray[i + (pageTileCount * pageDestination)]->transformation.translate.y = (h * tileHeight) + (tileDestinationY * tileHeight);


		if (w < (tw - 1))
		{
			w++;
		}

		else
		{
			w = 0;
			h--;
		}
	}
}

void TileMapManager::movePage(GLfloat tileDestinationX, GLfloat tileDestinationY, GLuint page)
{
	uint tw = viewPortW / tileWidth;
	uint th = viewPortH / tileHeight;

	uint w = 0;
	uint h = th - 1;

	for (uint i = 0; i < pageTileCount; i++)
	{
		tilesArray[i + (pageTileCount * page)]->transformation.translate.x = (w * tileWidth) + (tileDestinationX * tileWidth);
		tilesArray[i + (pageTileCount * page)]->transformation.translate.y = (h * tileHeight) + (tileDestinationY * tileHeight);

		if (w < (tw - 1))
		{
			w++;
		}

		else
		{
			w = 0;
			h--;
		}
	}
}

void TileMapManager::loadFirstPage(GLuint pageSource)
{
	loadPage(0, 0, pageSource, 0);
}

void TileMapManager::loadSecondPage(GLuint pageSource)
{
	loadPage(16, 0, pageSource, 1);
}

void TileMapManager::loadThirdPage(GLuint pageSource)
{
	loadPage(0, -15, pageSource, 2);
}

void TileMapManager::loadFourthPage(GLuint pageSource)
{
	loadPage(16, -15, pageSource, 3);
}

void TileMapManager::updateEnitities()
{
	GLuint offset = 0;
	vector<Sprite *>::iterator tait;

	if (tilesArray.size() > 0)
	{
		for (tait = tilesArray.begin(); tait != tilesArray.end(); tait++)
		{
			//Update all sprites
			(*tait)->update();

			//Copy data from Entities array to data array of floats
			updateVertexArray(*tait, offset);

			//Apply offset
			offset += quadFloatCount;
		}
	}
}

void TileMapManager::updateVertexArray(Sprite *sprite, GLuint offset)
{
	updatePosition( sprite, offset + 0);
	updateTexture(sprite, offset + 3);
	updateColor(sprite, offset + 7);
	updateTranslate(sprite, offset + 11);
	updateScale(sprite, offset + 14);
	updateRotate(sprite, offset + 17);
}

void TileMapManager::updatePosition(Sprite *sprite, GLuint offset)
{
   GLint pageDimensionX = 0;
   GLint pageDimensionY = 0;
	glBindTexture(GL_TEXTURE_2D_ARRAY, sprite->texturePalette);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &pageDimensionX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &pageDimensionY);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

  	//glVertex3f(-image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(float(pImage->w) - image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = (sprite->tileDimension.x / pageDimensionX) - sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(float(pImage->w) - image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = (sprite->tileDimension.x / pageDimensionX) - sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = (sprite->tileDimension.y / pageDimensionY) - sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(-image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value)
	vertexArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = (sprite->tileDimension.y / pageDimensionY) - sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
}

void TileMapManager::updateTexture(Sprite *sprite, GLuint offset)
{
   GLint pageDimensionX = 0;
   GLint pageDimensionY = 0;
	glBindTexture(GL_TEXTURE_2D_ARRAY, sprite->texturePalette);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &pageDimensionX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &pageDimensionY);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

  	GLfloat textureX = ( (sprite->tilePosition.x * sprite->tileDimension.x) + (tileSeparation *  sprite->tilePosition.x) ) / pageDimensionX;
	GLfloat textureY = ( (sprite->tilePosition.y * sprite->tileDimension.y) + (tileSeparation *  sprite->tilePosition.y) ) / pageDimensionY;
	GLfloat textureW = sprite->tileDimension.x / pageDimensionX;
	GLfloat textureH = sprite->tileDimension.y / pageDimensionY;

	if(sprite->ptrAnimation != nullptr)
	{
		sprite->ptrAnimation->update();
		textureX = ( ( (sprite->tilePosition.x + sprite->ptrAnimation->actualFrame) * tileWidth) + (tileSeparation *  sprite->tilePosition.x) ) / pageDimensionX;
	}

	//glTexCoord2f(image->textureX.value, image->textureY.value + image->textureHeight.value);
	vertexArray[offset] = textureX;
	offset++;
	vertexArray[offset] = textureY + textureH;
	offset++;
	vertexArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value + image->textureHeight.value);
	vertexArray[offset] = textureX + textureW;
	offset++;
	vertexArray[offset] = textureY + textureH;
	offset++;
	vertexArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value);
	vertexArray[offset] = textureX + textureW;
	offset++;
	vertexArray[offset] = textureY;
	offset++;
	vertexArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//glTexCoord2f(image->textureX.value, image->textureY.value);
	vertexArray[offset] = textureX;
	offset++;
	vertexArray[offset] = textureY;
	offset++;
	vertexArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePalette);
}

void TileMapManager::updateColor(Sprite *sprite, GLuint offset)
{
	vertexArray[offset] = sprite->vertexColor[0].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[0].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[0].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[0].a;
	offset += (20 - 3);

	vertexArray[offset] = sprite->vertexColor[1].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[1].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[1].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[1].a;
	offset += (20 - 3);

	vertexArray[offset] = sprite->vertexColor[2].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[2].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[2].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[2].a;
	offset += (20 - 3);

	vertexArray[offset] = sprite->vertexColor[3].r;
	offset++;
	vertexArray[offset] = sprite->vertexColor[3].g;
	offset++;
	vertexArray[offset] = sprite->vertexColor[3].b;
	offset++;
	vertexArray[offset] = sprite->vertexColor[3].a;
}

void TileMapManager::updateTranslate(Sprite *sprite, GLuint offset)
{
	vertexArray[offset] = sprite->transformation.translate.x + offsetX;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + offsetY;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + offsetX;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + offsetY;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + offsetX;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + offsetY;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + offsetX;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + offsetY;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
}

void TileMapManager::updateScale(Sprite *sprite, GLuint offset)
{
	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
}

void TileMapManager::updateRotate(Sprite *sprite, GLuint offset)
{

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
}

void TileMapManager::updateVertexBuffer()
{
	ptrVertexBuffer->attach();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexArray.size() * sizeof(GLfloat), vertexArray.data());
	ptrVertexBuffer->detach();
}

void TileMapManager::batchDraw()
{
	ptrVertexArray->attach();
	ptrVertexBuffer->attach();
	ptrIndexBuffer->attach();

	//Define offset to texture unit on vertex buffer
	GLuint offset = 6;
	//Draw vertices in groups of GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
	for (uint i = 0; i < batchDrawCalls; i++)
	{
		//Bind each quad texture to GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
		for (int j = 0; j < maxTextureUnits; j++)
		{
			if(vertexArray[offset] == 100)
            //Object is a rectangle//
			{
                glActiveTexture(0);
                glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
            }
			else
			//Object is a sprite//
			{
                glActiveTexture(GL_TEXTURE0 + GLint(vertexArray[offset]));
                glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(vertexArray[offset]));
         }

			for (uint k = 0; k < 4; k++)
			{
				batchDrawCount = i;
				textureCounter = j;
				vertexArray[offset] = j;
				offset += (vertexBufferStrideCount);
			}

		}
		glDrawRangeElements(drawingMode, i * batchDrawOffset, (i * batchDrawOffset) + batchDrawOffset, ptrIndexBuffer->bufferCount, GL_UNSIGNED_INT, 0);
	}
	ptrVertexArray->detach();
	ptrVertexBuffer->detach();
	ptrIndexBuffer->detach();
}

void TileMapManager::print() const
{
	printInfo();
	printSprites();
	printDataArray();
}

void TileMapManager::printInfo() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Tile Map Manager Info:" << endl;
	cout << "Offset X = " << offsetX << endl;
	cout << "Offset Y = " << offsetY << endl;
	cout << "Map Page Count = " << mapPageCount << endl;
	cout << "Page Tile Count = " << pageTileCount << endl;
	cout << "Actual Page = " << actualPage << endl;
	cout << "Batch Draw Calls = " << batchDrawCalls << endl;
	cout << "Batch Draw Offset = " << batchDrawOffset << endl;
	cout << "Entities Buffer Size = " << tilesArray.size() << endl;
	cout << "Data Buffer Size = " << vertexArray.size() << endl;
	cout << "Quad Count = " << vertexArray.size() / vertexBufferStrideCount << endl;
	cout << "Quad Float Count = " << quadFloatCount << endl;
	cout << "Vertex Buffer Stride Count = " << vertexBufferStrideCount << endl;
	cout << "Tile Map Manager Info:" << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}

void TileMapManager::printDataArray() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Buffer Data: " << endl;
	cout << "X---Y---Z---S---T---P---Q---R---G---B---A---Tx---Ty---Tz---Sx---Sy---Sz---Rx---Ry---Rz" << endl;

	for (uint i = 0; i < vertexArray.size(); i++)
	{
		if (i > 0)
		{
			if (i % vertexBufferStrideCount == 0)
				cout << endl;
		}
		cout << vertexArray[i] << ",    ";
	}

	cout << endl<< "Buffer Data: " << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}

void TileMapManager::printSprites() const
{
	cout << "**************************************************" << endl;
	cout << "Buffer Sprites: " << endl;

	for (GLuint i = 0; i < tilesArray.size(); i++)
		tilesArray[i]->print();

	cout << "Buffer Sprites: " << endl;
	cout << "**************************************************" << endl;
}

void TileMapManager::printTiles() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Tile Map Sprites: " << endl;

	uint w = 0;

	for (uint i = 0; i <tilesArray.size(); i++)
	{
		cout << "[ " << tilesArray[i]->tilePosition.x << "," << tilesArray[i]->tilePosition.y <<" ]";

		if (w < ((viewPortW / tileWidth) - 1))
			w++;
		else
		{
			w = 0;
			cout << "," << endl;
		}
	}
	cout << "Tile Map Sprites: " << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}

