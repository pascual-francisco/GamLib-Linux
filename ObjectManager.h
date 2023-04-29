#pragma once
#include "stdafx.h"

#ifndef OBJECTMANAGER_H
#define	OBJECTMANAGER_H

class ObjectManager
{
	private:
	GLuint vertexBufferStrideCount;
	GLuint quadFloatCount;
	GLuint batchDrawOffset;
	GLuint batchDrawCount;
	GLuint batchDrawCalls;
	GLuint textureCounter;
	GLint maxTextureUnits;

	  void updateDataArray(Sprite* sprite, GLuint offset);
	  void updatePosition(Sprite *sprite, GLuint offset);
	  void updateTexture(Sprite *sprite, GLuint offset);
	  void updateColor(Sprite *sprite, GLuint offset);
	  void updateTranslate(Sprite *sprite, GLuint offset);
	  void updateScale(Sprite *sprite, GLuint offset);
	  void updateRotate(Sprite *sprite, GLuint offset);
	  void updateEnitities();
	  void updateVertexBuffer();

	public:
	GLuint	programID;
	GLenum	drawingMode;
	vector<Entity *> entitiesArray;
	vector<float > dataArray;

	VertexBufferLayout	*ptrvPosLayout;
	VertexBufferLayout	*ptrvTexLayout;
	VertexBufferLayout	*ptrvColLayout;
	VertexBufferLayout	*ptrvTraLayout;
	VertexBufferLayout	*ptrvScaLayout;
	VertexBufferLayout	*ptrvRotLayout;
	IndexBuffer			*ptrIndexBuffer;
	VertexBuffer		*ptrVertexBuffer;
	VertexArray			*ptrVertexArray;

	  ObjectManager(GLuint program = 0, GLenum mode = GL_TRIANGLES);
	  ~ObjectManager();

	  void  initDataArray();
	  void	initBuffers();
	  void	initLayouts();
	  void  batchDraw(GLenum mode = GL_TRIANGLES);

	  void update();
	  void print() const;
	  void printInfo() const;
	  void printDataArray() const;
	  void printEntities() const;
};
#endif // !OBJECTMANAGER_H
