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
	GLuint  frameCounter;
    bool	mainPage;

	  void initBuffers();
	  void initLayouts();
	  void updateVertexArray(Sprite *sprite, GLuint offset);
	  void updatePosition(Sprite *sprite, GLuint offset);
	  void updateTexture(Sprite *sprite, GLuint offset);
	  void updateColor(Sprite *sprite, GLuint offset);
	  void updateTranslate(Sprite *sprite, GLuint offset);
	  void updateScale(Sprite *sprite, GLuint offset);
	  void updateRotate(Sprite *sprite, GLuint offset);
	  void updateEnitities();
	  void updateVertexBuffer();

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
	GLuint 	tileFrameTime;

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

	  TileMapManager(GLuint mapDataCount = 1, GLuint pageTiles = 224, GLuint *mapData = nullptr, GLuint viewportwidth = 256, GLuint viewportheight = 224, GLuint tilewidth = 16, GLuint tileheight = 16, GLuint tileseparation = 0, GLuint tileframetime = 0,  GLuint program = 0, GLenum mode = GL_TRIANGLES);
	  ~TileMapManager();
	  void batchDraw();
	  void update();
	  void loadTile();
	  void loadPage(GLfloat tileDestinationX = 0, GLfloat tileDestinationY = 0, GLuint pageSource = 0, GLuint pageDestination = 0);
	  void movePage(GLfloat tileDestinationX = 0, GLfloat tileDestinationY = 0, GLuint page = 0);
	  void loadFirstPage(GLuint pageSource = 0);
	  void loadSecondPage(GLuint pageSource = 0);
	  void loadThirdPage(GLuint pageSource = 0);
	  void loadFourthPage(GLuint pageSource = 0);
	  void print() const;
	  void printInfo() const;
	  void printDataArray() const;
	  void printSprites() const;
	  void printTiles() const;
};
#endif // !TILEMAPMANAGER_H
