#include "stdafx.h"

ObjectManager::ObjectManager(GLuint program, GLenum mode)
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

	programID = program;
	drawingMode = mode;
	maxTextureUnits = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	batchDrawOffset = maxTextureUnits * 6;
	batchDrawCount = 0;
	batchDrawCalls = 0;
	textureCounter = 0;
	vertexBufferStrideCount = 20;
	quadFloatCount = 80;
}

ObjectManager::~ObjectManager()
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

void ObjectManager::initDataArray()
{
	GLuint sprites = 0;
	GLuint vertices = 4;

	vector<Entity *>::iterator eit;
	vector<Sprite *>::iterator sit;
	vector<float >::iterator dit;

	if (entitiesArray.size() > 0)
	{
		for (eit = entitiesArray.begin(); eit != entitiesArray.end(); eit++)
		{
			if ((*eit) != nullptr)
			{
				for (sit = (*eit)->sprite.begin(); sit != (*eit)->sprite.end(); sit++)
				{
					if ((*sit) != nullptr)
					{
						sprites++;
					}
				}
			}
		}
	}

	dataArray = vector<float>(sprites * vertices * vertexBufferStrideCount);

	initBuffers();
	initLayouts();
	updateEnitities();
}

void ObjectManager::initBuffers()
{
	//Vertex Array//
	ptrVertexArray = new VertexArray();

	//Vertex Buffer//
	ptrVertexBuffer = new VertexBuffer(dataArray.size(), sizeof(GLfloat), dataArray.data());

	//Index Buffer//
	ptrIndexBuffer = new IndexBuffer(6 * (dataArray.size() / quadFloatCount), sizeof(GL_UNSIGNED_INT), nullptr);

	batchDrawCalls = ptrIndexBuffer->bufferCount / batchDrawOffset;
}

void ObjectManager::initLayouts()
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

void ObjectManager::updateEnitities()
{
	GLuint offset = 0;
	vector<Entity *>::iterator eit;
	vector<Sprite *>::iterator sit;

	if (entitiesArray.size() > 0)
	{
		for (eit = entitiesArray.begin(); eit != entitiesArray.end(); eit++)
		{
			if ((*eit) != nullptr)
			{
				(*eit)->update();

				(*eit)->mechanics.speed.x += (*eit)->mechanics.acceleration.x;
				(*eit)->mechanics.speed.y += (*eit)->mechanics.acceleration.y;

				(*eit)->mechanics.position.x += (*eit)->mechanics.speed.x;
				(*eit)->mechanics.position.y += (*eit)->mechanics.speed.y;

				if ((*eit)->sprite.size() > 0)
				{
					for (sit = (*eit)->sprite.begin(); sit != (*eit)->sprite.end(); sit++)
					{
						(*sit)->transformation.translate.x = (*sit)->positionOffset.x + (*eit)->mechanics.position.x;
						(*sit)->transformation.translate.y = (*sit)->positionOffset.y + (*eit)->mechanics.position.y;

						(*sit)->update();

						updateDataArray(*sit, offset);

						offset += quadFloatCount;
					}
				}
			}
		}
	}
}

void ObjectManager::updateVertexBuffer()
{
	ptrVertexBuffer->attach();
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataArray.size() * sizeof(GLfloat), dataArray.data());
	ptrVertexBuffer->detach();
}

void ObjectManager::updateDataArray(Sprite *sprite, GLuint offset)
{
	updatePosition(sprite, offset + 0);
	updateTexture(sprite, offset + 3);
	updateColor(sprite, offset + 7);
	updateTranslate(sprite, offset + 11);
	updateScale(sprite, offset + 14);
	updateRotate(sprite, offset + 17);
}

void ObjectManager::updatePosition(Sprite *sprite, GLuint offset)
{
   GLint pageDimensionX = 0;
   GLint pageDimensionY = 0;

	glBindTexture(GL_TEXTURE_2D_ARRAY, sprite->texturePalette);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &pageDimensionX);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &pageDimensionY);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

   //glVertex3f(-image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	dataArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(float(pImage->w) - image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);
	dataArray[offset] = (sprite->tileDimension.x / pageDimensionX) - sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(float(pImage->w) - image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value);
	dataArray[offset] = (sprite->tileDimension.x / pageDimensionX) - sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = (sprite->tileDimension.y / pageDimensionY) - sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
	offset += (20 - 2);

	//glVertex3f(-image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value)
	dataArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = (sprite->tileDimension.y / pageDimensionY) - sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
}

void ObjectManager::updateTexture(Sprite *sprite, GLuint offset)
{
   //glTexCoord2f(image->textureX.value, image->textureY.value + image->textureHeight.value);
	dataArray[offset] = sprite->tilePosition.x;
	offset++;
	dataArray[offset] = sprite->tilePosition.y + sprite->tileDimension.y;
	offset++;
	dataArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	dataArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value + image->textureHeight.value);
	dataArray[offset] = sprite->tilePosition.x + sprite->tileDimension.x;
	offset++;
	dataArray[offset] = sprite->tilePosition.y + sprite->tileDimension.y;
	offset++;
	dataArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	dataArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value);
	dataArray[offset] = sprite->tilePosition.x + sprite->tileDimension.x;
	offset++;
	dataArray[offset] = sprite->tilePosition.y;
	offset++;
	dataArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	dataArray[offset] = GLfloat(sprite->texturePalette);
	offset += (20 - 3);

	//glTexCoord2f(image->textureX.value, image->textureY.value);
	dataArray[offset] = sprite->tilePosition.x;
	offset++;
	dataArray[offset] = sprite->tilePosition.y;
	offset++;
	dataArray[offset] = GLfloat(sprite->palettePage);
	offset++;
	dataArray[offset] = GLfloat(sprite->texturePalette);
}

void ObjectManager::updateColor(Sprite *sprite, GLuint offset)
{
	dataArray[offset] = sprite->vertexColor[0].r;
	offset++;
	dataArray[offset] = sprite->vertexColor[0].g;
	offset++;
	dataArray[offset] = sprite->vertexColor[0].b;
	offset++;
	dataArray[offset] = sprite->vertexColor[0].a;
	offset += (20 - 3);

	dataArray[offset] = sprite->vertexColor[1].r;
	offset++;
	dataArray[offset] = sprite->vertexColor[1].g;
	offset++;
	dataArray[offset] = sprite->vertexColor[1].b;
	offset++;
	dataArray[offset] = sprite->vertexColor[1].a;
	offset += (20 - 3);

	dataArray[offset] = sprite->vertexColor[2].r;
	offset++;
	dataArray[offset] = sprite->vertexColor[2].g;
	offset++;
	dataArray[offset] = sprite->vertexColor[2].b;
	offset++;
	dataArray[offset] = sprite->vertexColor[2].a;
	offset += (20 - 3);

	dataArray[offset] = sprite->vertexColor[3].r;
	offset++;
	dataArray[offset] = sprite->vertexColor[3].g;
	offset++;
	dataArray[offset] = sprite->vertexColor[3].b;
	offset++;
	dataArray[offset] = sprite->vertexColor[3].a;
}

void ObjectManager::updateTranslate(Sprite *sprite, GLuint offset)
{
	dataArray[offset] = sprite->transformation.translate.x;
	offset++;
	dataArray[offset] = sprite->transformation.translate.y;
	offset++;
	dataArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.translate.x;
	offset++;
	dataArray[offset] = sprite->transformation.translate.y;
	offset++;
	dataArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.translate.x;
	offset++;
	dataArray[offset] = sprite->transformation.translate.y;
	offset++;
	dataArray[offset] = sprite->transformation.translate.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.translate.x;
	offset++;
	dataArray[offset] = sprite->transformation.translate.y;
	offset++;
	dataArray[offset] = sprite->transformation.translate.z;

}

void ObjectManager::updateScale(Sprite *sprite, GLuint offset)
{
	dataArray[offset] = sprite->transformation.scale.x;
	offset++;
	dataArray[offset] = sprite->transformation.scale.y;
	offset++;
	dataArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.scale.x;
	offset++;
	dataArray[offset] = sprite->transformation.scale.y;
	offset++;
	dataArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.scale.x;
	offset++;
	dataArray[offset] = sprite->transformation.scale.y;
	offset++;
	dataArray[offset] = sprite->transformation.scale.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.scale.x;
	offset++;
	dataArray[offset] = sprite->transformation.scale.y;
	offset++;
	dataArray[offset] = sprite->transformation.scale.z;
}

void ObjectManager::updateRotate(Sprite *sprite, GLuint offset)
{

	dataArray[offset] = sprite->transformation.rotate.x;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.y;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.rotate.x;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.y;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.rotate.x;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.y;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.z;
	offset += (20 - 2);

	dataArray[offset] = sprite->transformation.rotate.x;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.y;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.z;
}

void ObjectManager::batchDraw(GLenum mode)
{
	drawingMode = mode;

	ptrVertexArray->attach();
	ptrVertexBuffer->attach();
	ptrIndexBuffer->attach();

	//Define offset to texture unit on vertex buffer
	GLuint offset = 6;

	if ((dataArray.size() / quadFloatCount) < GLuint(maxTextureUnits))
	{
		//Bind each quad texture to GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS texture units
		for (uint j = 0; j < (dataArray.size() / quadFloatCount); j++)
		{
                if(dataArray[offset] == 100)
                //Object is a rectangle//
				{
                    glActiveTexture(0);
                    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
                }
				else
				//Object is a sprite//
				{
                    glActiveTexture(GL_TEXTURE0 + GLint(dataArray[offset]));
                    glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(dataArray[offset]));
				}

			for (uint k = 0; k < 4; k++)
			{
				dataArray[offset] = GLfloat(j);
				offset += (vertexBufferStrideCount);
			}
		}
		glDrawRangeElements(drawingMode, 0, ptrIndexBuffer->bufferCount, ptrIndexBuffer->bufferCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		//Draw vertices in groups of GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
		for (uint i = 0; i < batchDrawCalls; i++)
		{
			//Bind each quad texture to GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
			for (int j = 0; j < maxTextureUnits; j++)
			{
				if(dataArray[offset] == 100)
				//Object is a rectangle//
				{
                    glActiveTexture(0);
                    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
                }
				else
				//Object is a sprite//
				{
                    glActiveTexture(GL_TEXTURE0 + GLint(dataArray[offset]));
                    glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(dataArray[offset]));
				}

				for (uint k = 0; k < 4; k++)
				{
					batchDrawCount = i;
					textureCounter = j;

					dataArray[offset] = GLfloat(j);
					offset += (vertexBufferStrideCount);
				}
			}
			glDrawRangeElements(drawingMode, i * batchDrawOffset, (i * batchDrawOffset) + batchDrawOffset, ptrIndexBuffer->bufferCount, GL_UNSIGNED_INT, 0);
		}
	}
	ptrVertexArray->detach();
	ptrVertexBuffer->detach();
	ptrIndexBuffer->detach();
}

void ObjectManager::update()
{
	updateEnitities();
	updateVertexBuffer();
}

void ObjectManager::print() const
{
	printInfo();
	printEntities();
	printDataArray();
}

void ObjectManager::printInfo() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Object Manager Info:" << endl;
	cout << "Program ID = " << programID << endl;
	cout << "Batch Draw Calls = " << batchDrawCalls << endl;
	cout << "Batch Draw Offset = " << batchDrawOffset<< endl;
	cout << "Entities Buffer Size = " << entitiesArray.size() << endl;
	cout << "Data Buffer Size = " << dataArray.size() << endl;
	cout << "Quad Count = " << dataArray.size() / quadFloatCount << endl;
	cout << "Quad Float Count = "<<quadFloatCount << endl;
	cout << "Vertex Buffer Stride Count = " <<vertexBufferStrideCount << endl;
	cout << "Object Manager Info:" << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}

void ObjectManager::printDataArray() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Buffer Data: " << endl;
	cout << "X---Y---Z---S---T---P---Q---R---G---B---A---Tx---Ty---Tz---Sx---Sy---Sz---Rx---Ry---Rz" << endl;

	for (uint i = 0; i < dataArray.size(); i++)
	{
		if (i > 0)
		{
			if (i % vertexBufferStrideCount == 0)
				cout << endl;
		}
		cout << dataArray[i] << ",    ";
	}

	cout <<endl<< "Buffer Data: " << endl;
	cout <<endl<< "******************************************************************************************************************************************************************************" << endl;
}

void ObjectManager::printEntities() const
{
	cout << "**************************************************" << endl;
	cout << "Buffer Entities Data: " << endl;

	for (GLuint i = 0; i < entitiesArray.size(); i++)
		entitiesArray[i]->print();

	cout << "Buffer Entities Data: " << endl;
	cout << "**************************************************" << endl;
}
