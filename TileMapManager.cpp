#pragma once
#include "stdafx.h"

TileMapManager::TileMapManager(GLuint mapDataCount, GLuint pageTiles, GLuint *mapData, GLuint vw, GLuint vh, GLuint tw, GLuint th, GLuint tz, GLuint program, GLenum mode)
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
	vertexBufferStrideCount = 21;
	quadFloatCount = 84;
	programID = program;
	tileWidth = tw;
	tileHeight = th;
	tileSeparation = tz;
	viewPortW = vw;
	viewPortH = vh;
	drawingMode = mode;
	maxTextureUnits = 0;

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	batchDrawOffset = maxTextureUnits * 6;
	pageTileCount = pageTiles;
	mapPageCount = mapDataCount / pageTileCount;

	mapTilesArray = vector<Sprite *>(mapDataCount);
	tilesArray = vector<Sprite *>( pageTileCount * 4);
	vertexArray = vector<float>(tilesArray.size() * vertexBufferStrideCount * 4);

	vector<Sprite *>::iterator mtit;
	vector<Sprite *>::iterator tait;
	vector<float >::iterator vait;

	BYTE palette = 0x00;
	BYTE palettePage = 0x00;
	WORD tileColumn = 0x0000;
	WORD tileRow = 0x0000;
	WORD tileFrames = 0x0000;

	//Init all the tiles from the array of data
	/*
	//[Palette,Page-Column-Row-Frames-Size,Seperation-Collision]
	 int  x = 0x2501010A;
    cout<<" palette = " << ( (x & 0xF0000000) >> 28 )  <<endl;
    cout<<" page = " <<    ( (x & 0x0F000000) >> 24 )  <<endl;
    cout<<" column = " <<  ( (x & 0x00FF0000) >> 16 )  <<endl;
    cout<<" row = " <<     ( (x & 0x0000FF00) >> 8 )  <<endl;
    cout<<" frames = " <<  ( (x & 0x000000FF)   )  <<endl;
	*/

	if (mapTilesArray.size() > 0)
	{
		uint i = 0;

		for (mtit = mapTilesArray.begin(); mtit != mapTilesArray.end(); mtit++)
		{
			palette = ((mapData[i] & 0xF0000000) >> 28);
			palettePage = ((mapData[i] & 0x0F000000) >> 24);
			tileColumn = ((mapData[i] & 0x00FF0000) >> 16);
			tileRow = ((mapData[i] & 0x0000FF00) >> 8);
			tileFrames = ((mapData[i] & 0x000000FF) );


			(*mtit) = new Sprite(palette, palettePage, tw *  tileColumn, th * tileRow, tw, th, tz, 0, tileFrames, 0, 3, 0);
			(*mtit)->hitBox.push_back(new HitBox());
			i++;
		}
	}

	//Init 4 pages of tiles for copy to vertex buffer
	if (tilesArray.size() > 0)
	{
		for (tait = tilesArray.begin(); tait != tilesArray.end(); tait++)
		{
			(*tait) = new Sprite();
			(*tait)->hitBox.push_back(new HitBox());
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
		Sprite 0 [XYZW-STPQ-RGBA-TTT-SSS-RRR] , [XYZW-STRQ-RGBA-TTT-SSS-RRR] , [XYZW-STRQ-RGBA-TTT-SSS-RRR] , [XYZW-STRQ-RGBA-TTT-SSS-RRR] = 21 Floats
		21 Float * 4 Vertices = 84 Floats
		1 Quad = 84 Floats
	*/
	ptrvPosLayout = new VertexBufferLayout(programID, "vPos", 4, GL_FALSE, 21, 0 * 4);
	ptrvTexLayout = new VertexBufferLayout(programID, "vTex", 4, GL_FALSE, 21, 4 * 4);
	ptrvColLayout = new VertexBufferLayout(programID, "vCol", 4, GL_FALSE, 21, 8 * 4);
	ptrvTraLayout = new VertexBufferLayout(programID, "vTra", 3, GL_FALSE, 21, 12 * 4);
	ptrvScaLayout = new VertexBufferLayout(programID, "vSca", 3, GL_FALSE, 21, 15 * 4);
	ptrvRotLayout = new VertexBufferLayout(programID, "vRot", 3, GL_FALSE, 21, 18 * 4);

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
	updateTexture(sprite, offset + 4);
	updateColor(sprite, offset + 8);
	updateTranslate(sprite, offset + 12);
	updateScale(sprite, offset + 15);
	updateRotate(sprite, offset + 18);
}

void TileMapManager::updatePosition(Sprite *sprite, GLuint offset)
{
	GLint w = 0;
	GLint h = 0;
	GLint d = 0;

	glBindTexture(GL_TEXTURE_2D_ARRAY, sprite->textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &w);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &h);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_DEPTH, &d);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	//glVertex3f(-image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	vertexArray[offset] = 1;
	offset += (21 - 3);

	//glVertex3f(float(pImage->w) - image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = sprite->textureOffset.z - sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	vertexArray[offset] = 1;
	offset += (21 - 3);

	//glVertex3f(float(pImage->w) - image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value);
	vertexArray[offset] = sprite->textureOffset.z - sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = sprite->textureOffset.w - sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	vertexArray[offset] = 1;
	offset += (21 - 3);

	//glVertex3f(-image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value)
	vertexArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	vertexArray[offset] = sprite->textureOffset.w - sprite->transformation.pivot.y;
	offset++;
	vertexArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	vertexArray[offset] = 1;
}

void TileMapManager::updateTexture(Sprite *sprite, GLuint offset)
{
	//glTexCoord2f(image->textureX.value, image->textureY.value + image->textureHeight.value);
	vertexArray[offset] = sprite->textureOffset.x;
	offset++;
	vertexArray[offset] = sprite->textureOffset.y + sprite->textureOffset.w;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePageOffset);
	offset++;
	vertexArray[offset] = GLfloat(sprite->textureID);
	offset += (21 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value + image->textureHeight.value);
	vertexArray[offset] = sprite->textureOffset.x + sprite->textureOffset.z;
	offset++;
	vertexArray[offset] = sprite->textureOffset.y + sprite->textureOffset.w;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePageOffset);
	offset++;
	vertexArray[offset] = GLfloat(sprite->textureID);
	offset += (21 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value);
	vertexArray[offset] = sprite->textureOffset.x + sprite->textureOffset.z;
	offset++;
	vertexArray[offset] = sprite->textureOffset.y;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePageOffset);
	offset++;
	vertexArray[offset] = GLfloat(sprite->textureID);
	offset += (21 - 3);

	//glTexCoord2f(image->textureX.value, image->textureY.value);
	vertexArray[offset] = sprite->textureOffset.x;
	offset++;
	vertexArray[offset] = sprite->textureOffset.y;
	offset++;
	vertexArray[offset] = GLfloat(sprite->texturePageOffset);
	offset++;
	vertexArray[offset] = GLfloat(sprite->textureID);
}

void TileMapManager::updateColor(Sprite *sprite, GLuint offset)
{
	vertexArray[offset] = sprite->color[0].r;
	offset++;
	vertexArray[offset] = sprite->color[0].g;
	offset++;
	vertexArray[offset] = sprite->color[0].b;
	offset++;
	vertexArray[offset] = sprite->color[0].a;
	offset += (21 - 3);

	vertexArray[offset] = sprite->color[1].r;
	offset++;
	vertexArray[offset] = sprite->color[1].g;
	offset++;
	vertexArray[offset] = sprite->color[1].b;
	offset++;
	vertexArray[offset] = sprite->color[1].a;
	offset += (21 - 3);

	vertexArray[offset] = sprite->color[2].r;
	offset++;
	vertexArray[offset] = sprite->color[2].g;
	offset++;
	vertexArray[offset] = sprite->color[2].b;
	offset++;
	vertexArray[offset] = sprite->color[2].a;
	offset += (21 - 3);

	vertexArray[offset] = sprite->color[3].r;
	offset++;
	vertexArray[offset] = sprite->color[3].g;
	offset++;
	vertexArray[offset] = sprite->color[3].b;
	offset++;
	vertexArray[offset] = sprite->color[3].a;
}

void TileMapManager::updateTranslate(Sprite *sprite, GLuint offset)
{
	sprite->hitBox[0]->box.x = sprite->transformation.translate.x + offsetX;
	sprite->hitBox[0]->box.y = sprite->transformation.translate.y + offsetY;
	sprite->hitBox[0]->box.w = tileWidth;
	sprite->hitBox[0]->box.h = tileHeight;

	vertexArray[offset] = sprite->transformation.translate.x + offsetX;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + offsetY;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (21 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + offsetX;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + offsetY;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (21 - 2);

	vertexArray[offset] = sprite->transformation.translate.x + offsetX;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.y + offsetY;
	offset++;
	vertexArray[offset] = sprite->transformation.translate.z;
	offset += (21 - 2);

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
	offset += (21 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (21 - 2);

	vertexArray[offset] = sprite->transformation.scale.x;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.y;
	offset++;
	vertexArray[offset] = sprite->transformation.scale.z;
	offset += (21 - 2);

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
	offset += (21 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (21 - 2);

	vertexArray[offset] = sprite->transformation.rotate.x;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.y;
	offset++;
	vertexArray[offset] = sprite->transformation.rotate.z;
	offset += (21 - 2);

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
	GLuint offset = 7;
	//Draw vertices in groups of 32
	for (uint i = 0; i < batchDrawCalls; i++)
	{
		//Bind each quad texture to 32 texture units
		for (int j = 0; j < maxTextureUnits; j++)
		{
			glActiveTexture(GL_TEXTURE0 + GLuint(vertexArray[offset]));
			glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(vertexArray[offset]));

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
	printSprites();
}

void TileMapManager::printInfo() const
{
	cout << "**************************************************" << endl;
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
	cout << "**************************************************" << endl;
}

void TileMapManager::printDataArray() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Buffer Data: " << endl;

	for (uint i = 0; i < vertexArray.size(); i++)
	{
		if (i > 0)
		{
			if (i % vertexBufferStrideCount == 0)
				cout << endl;
		}
		cout << vertexArray[i] << ",    ";
	}

	cout << endl << "******************************************************************************************************************************************************************************" << endl;
}

void TileMapManager::printSprites() const
{
	cout << "**************************************************" << endl;
	cout << "Buffer Sprites: " << endl;

	for (GLuint i = 0; i < tilesArray.size(); i++)
		tilesArray[i]->print();

	cout << "**************************************************" << endl;
}

void TileMapManager::printTiles() const
{
	uint w = 0;

	for (uint i = 0; i <tilesArray.size(); i++)
	{
		cout << "[ " << tilesArray[i]->textureID << " ]";

		if (w < ((viewPortW / tileWidth) - 1))
			w++;
		else
		{
			w = 0;
			cout << "," << endl;
		}
	}
}

