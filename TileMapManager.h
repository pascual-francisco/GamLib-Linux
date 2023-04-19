#pragma once
#include "stdafx.h"

#ifndef TILEMAPMANAGER_H
#define	TILEMAPMANAGER_H

class TileMapManager
{
	private:
	GLuint	vertexBufferStrideCount;
	GLuint	quadFloatCount;
	GLuint	batchDrawOffset;
	GLuint	batchDrawCount;
	GLuint	batchDrawCalls;
	GLuint	textureCounter;
	GLint	maxTextureUnits;
	GLuint	actualPage;
	bool	mainPage;

	__declspec(dllexport) void initBuffers();
	__declspec(dllexport) void initLayouts();
	__declspec(dllexport) void updateVertexArray(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updatePosition(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateTexture(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateColor(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateTranslate(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateScale(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateRotate(Sprite *sprite, GLuint offset);
	__declspec(dllexport) void updateEnitities();
	__declspec(dllexport) void updateVertexBuffer();

	public:
	GLfloat offsetX;
	GLfloat	offsetY;
	GLfloat	speedX;
	GLfloat	speedY;
	GLuint	tileWidth;
	GLuint	tileHeight;
	GLuint	viewPortW;
	GLuint	viewPortH;
	GLuint	programID;
	GLenum	drawingMode;
	GLuint	mapPageCount;
	GLuint  pageTileCount;
	GLuint	tileSeparation;

	vector<Sprite *>	mapTilesArray;
	vector<Sprite *>	tilesArray;
	vector<float>		vertexArray;

	VertexBufferLayout	*ptrvPosLayout;
	VertexBufferLayout	*ptrvTexLayout;
	VertexBufferLayout	*ptrvColLayout;
	VertexBufferLayout	*ptrvTraLayout;
	VertexBufferLayout	*ptrvScaLayout;
	VertexBufferLayout	*ptrvRotLayout;
	IndexBuffer			*ptrIndexBuffer;
	VertexBuffer		*ptrVertexBuffer;
	VertexArray			*ptrVertexArray;

	__declspec(dllexport) TileMapManager(GLuint mapDataCount = 1, GLuint pageTiles = 224, GLuint *mapData = nullptr, GLuint vw = 256, GLuint vh = 224, GLuint tw = 16, GLuint th = 16, GLuint tz = 0,  GLuint program = 0, GLenum mode = GL_TRIANGLES);
	__declspec(dllexport) ~TileMapManager();
	__declspec(dllexport) void batchDraw();
	__declspec(dllexport) void update();
	__declspec(dllexport) void loadTile();
	__declspec(dllexport) void loadPage(GLfloat tileDestinationX = 0, GLfloat tileDestinationY = 0, GLuint pageSource = 0, GLuint pageDestination = 0);
	__declspec(dllexport) void movePage(GLfloat tileDestinationX = 0, GLfloat tileDestinationY = 0, GLuint page = 0);
	__declspec(dllexport) void loadFirstPage(GLuint pageSource = 0);
	__declspec(dllexport) void loadSecondPage(GLuint pageSource = 0);
	__declspec(dllexport) void loadThirdPage(GLuint pageSource = 0);
	__declspec(dllexport) void loadFourthPage(GLuint pageSource = 0);
	__declspec(dllexport) void print() const;
	__declspec(dllexport) void printInfo() const;
	__declspec(dllexport) void printDataArray() const;
	__declspec(dllexport) void printSprites() const;
	__declspec(dllexport) void printTiles() const;
};
#endif // !TILEMAPMANAGER_H
