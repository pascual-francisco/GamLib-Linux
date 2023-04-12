#pragma once
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
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	batchDrawOffset = maxTextureUnits * 6;
	batchDrawCount = 0;
	batchDrawCalls = 0;
	textureCounter = 0;
	vertexBufferStrideCount = 21;
	quadFloatCount = 84;					
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

void ObjectManager::updateEnitities()
{
	GLuint offset = 0;
	/*
	SDL_Rect viewPort;
	SDL_Rect sprite;
	viewPort.x = 0;
	viewPort.y = 0;
	viewPort.w = 256;
	viewPort.h = 224;
	*/

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
	updateTexture(sprite, offset + 4);	
	updateColor(sprite, offset + 8);	
	updateTranslate(sprite, offset + 12);
	updateScale(sprite, offset + 15);
	updateRotate(sprite, offset + 18);
}

void ObjectManager::updatePosition(Sprite *sprite, GLuint offset)
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
	dataArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	dataArray[offset] = 1;
	offset += (21 - 3);

	//glVertex3f(float(pImage->w) - image->pivotX.value, -image->pivotY.value, -image->pivotZ.value);	
	dataArray[offset] = w - sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	dataArray[offset] = 1;
	offset += (21 - 3);

	//glVertex3f(float(pImage->w) - image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value);	
	dataArray[offset] = w - sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = h - sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	dataArray[offset] = 1;
	offset += (21 - 3);

	//glVertex3f(-image->pivotX.value, float(pImage->h) - image->pivotY.value, -image->pivotZ.value)
	dataArray[offset] = -sprite->transformation.pivot.x;
	offset++;
	dataArray[offset] = h - sprite->transformation.pivot.y;
	offset++;
	dataArray[offset] = -sprite->transformation.pivot.z;
	offset++;
	dataArray[offset] = 1; 
}

void ObjectManager::updateTexture(Sprite *sprite, GLuint offset)
{			
	//glTexCoord2f(image->textureX.value, image->textureY.value + image->textureHeight.value);
	dataArray[offset] = sprite->textureOffset.x;
	offset++;
	dataArray[offset] = sprite->textureOffset.y + sprite->textureOffset.w;
	offset++;
	dataArray[offset] = GLfloat(sprite->actualFrame);
	offset++;
	dataArray[offset] = GLfloat(sprite->textureID);
	offset += (21 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value + image->textureHeight.value);
	dataArray[offset] = sprite->textureOffset.x + sprite->textureOffset.z;
	offset++;
	dataArray[offset] = sprite->textureOffset.y + sprite->textureOffset.w;
	offset++;
	dataArray[offset] = GLfloat(sprite->actualFrame);
	offset++;
	dataArray[offset] = GLfloat(sprite->textureID);
	offset += (21 - 3);

	//glTexCoord2f(image->textureX.value + image->textureWidth.value, image->textureY.value);
	dataArray[offset] = sprite->textureOffset.x + sprite->textureOffset.z;
	offset++;
	dataArray[offset] = sprite->textureOffset.y;
	offset++;
	dataArray[offset] = GLfloat(sprite->actualFrame);
	offset++;
	dataArray[offset] = GLfloat(sprite->textureID);
	offset += (21 - 3);

	//glTexCoord2f(image->textureX.value, image->textureY.value);
	dataArray[offset] = sprite->textureOffset.x;
	offset++;
	dataArray[offset] = sprite->textureOffset.y;
	offset++;
	dataArray[offset] = GLfloat(sprite->actualFrame);
	offset++;
	dataArray[offset] = GLfloat(sprite->textureID);
}

void ObjectManager::updateColor(Sprite *sprite, GLuint offset)
{
	dataArray[offset] = sprite->color[0].r;
	offset++;
	dataArray[offset] = sprite->color[0].g;
	offset++;
	dataArray[offset] = sprite->color[0].b;
	offset++;
	dataArray[offset] = sprite->color[0].a;
	offset += (21 - 3);

	dataArray[offset] = sprite->color[1].r;
	offset++;
	dataArray[offset] = sprite->color[1].g;
	offset++;
	dataArray[offset] = sprite->color[1].b;
	offset++;
	dataArray[offset] = sprite->color[1].a;
	offset += (21 - 3);

	dataArray[offset] = sprite->color[2].r;
	offset++;
	dataArray[offset] = sprite->color[2].g;
	offset++;
	dataArray[offset] = sprite->color[2].b;
	offset++;
	dataArray[offset] = sprite->color[2].a;
	offset += (21 - 3);

	dataArray[offset] = sprite->color[3].r;
	offset++;
	dataArray[offset] = sprite->color[3].g;
	offset++;
	dataArray[offset] = sprite->color[3].b;
	offset++;
	dataArray[offset] = sprite->color[3].a;
}

void ObjectManager::updateTranslate(Sprite *sprite, GLuint offset)
{
	dataArray[offset] = sprite->transformation.translate.x;
	offset++;
	dataArray[offset] = sprite->transformation.translate.y;
	offset++;
	dataArray[offset] = sprite->transformation.translate.z;
	offset += (21 - 2);

	dataArray[offset] = sprite->transformation.translate.x;
	offset++;
	dataArray[offset] = sprite->transformation.translate.y;
	offset++;
	dataArray[offset] = sprite->transformation.translate.z;
	offset += (21 - 2);

	dataArray[offset] = sprite->transformation.translate.x;
	offset++;
	dataArray[offset] = sprite->transformation.translate.y;
	offset++;
	dataArray[offset] = sprite->transformation.translate.z;
	offset += (21 - 2);

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
	offset += (21 - 2);

	dataArray[offset] = sprite->transformation.scale.x;
	offset++;
	dataArray[offset] = sprite->transformation.scale.y;
	offset++;
	dataArray[offset] = sprite->transformation.scale.z;
	offset += (21 - 2);

	dataArray[offset] = sprite->transformation.scale.x;
	offset++;
	dataArray[offset] = sprite->transformation.scale.y;
	offset++;
	dataArray[offset] = sprite->transformation.scale.z;
	offset += (21 - 2);

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
	offset += (21 - 2);

	dataArray[offset] = sprite->transformation.rotate.x;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.y;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.z;
	offset += (21 - 2);

	dataArray[offset] = sprite->transformation.rotate.x;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.y;
	offset++;
	dataArray[offset] = sprite->transformation.rotate.z;
	offset += (21 - 2);

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
	GLuint offset = 7;

	if ((dataArray.size() / quadFloatCount) < GLuint(maxTextureUnits))
	{
		//Bind each quad texture to 32 texture units
		for (uint j = 0; j < (dataArray.size() / quadFloatCount); j++)
		{
			glActiveTexture(GL_TEXTURE0 + GLuint(dataArray[offset]));
			glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(dataArray[offset]));
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
		//Draw vertices in groups of 32
		for (uint i = 0; i < batchDrawCalls; i++)
		{
			//Bind each quad texture to 32 texture units
			for (int j = 0; j < maxTextureUnits; j++)
			{		
				glActiveTexture(GL_TEXTURE0 + GLint(dataArray[offset]));
				glBindTexture(GL_TEXTURE_2D_ARRAY, GLuint(dataArray[offset]));

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
	cout << "**************************************************" << endl;
	cout << "Object Manager Info:" << endl;
	cout << "Program ID = " << programID << endl;
	cout << "Batch Draw Calls = " << batchDrawCalls << endl;
	cout << "Batch Draw Offset = " << batchDrawOffset<< endl;
	cout << "Entities Buffer Size = " << entitiesArray.size() << endl;
	cout << "Data Buffer Size = " << dataArray.size() << endl;
	cout << "Quad Count = " << dataArray.size() / quadFloatCount << endl;
	cout << "Quad Float Count = "<<quadFloatCount << endl;
	cout << "Vertex Buffer Stride Count = " <<vertexBufferStrideCount << endl;
	cout << "**************************************************" << endl;
}

void ObjectManager::printDataArray() const
{	
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Buffer Data: " << endl;
	
	for (uint i = 0; i < dataArray.size(); i++)
	{
		if (i > 0)
		{
			if (i % vertexBufferStrideCount == 0)
				cout << endl;			
		}
		cout << dataArray[i] << ",    ";
	}
	
	cout <<endl<< "******************************************************************************************************************************************************************************" << endl;
}

void ObjectManager::printEntities() const
{	
	cout << "**************************************************" << endl;
	cout << "Buffer Entities: " << endl;

	for (GLuint i = 0; i < entitiesArray.size(); i++)
		entitiesArray[i]->print();	

	cout << "**************************************************" << endl;
}

/*/

if (entitiesArrayCount > 0)
{
	for (GLuint i = 0; i < entitiesArrayCount; i++)
	{
		entitiesArray[i]->update();

		if (entitiesArray[i]->sprite != nullptr)
		{
			if (entitiesArray[i]->spriteCount > 0)
			{
				for (GLuint j = 0; j < entitiesArray[i]->spriteCount; j++)
				{
					entitiesArray[i]->sprite[j].update();
					updateDataArray(i, j, offset);
					offset += quadFloatCount;
				}
			}
		}
	}
}
}*/