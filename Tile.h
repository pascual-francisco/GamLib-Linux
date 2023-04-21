#pragma once
#include "stdafx.h"

#ifndef TILE_H
#define TILE_H

class Tile : public GraphicElement
{
	public:
	GLuint			texturePalette;
	Glfloat			textureOffset;
	vec4			color[4];
	GLubyte			collisionData;

	GLint			firstFrame;
	GLint			lastFrame;
	GLint			actualFrame;
	GLfloat			frameCounter;
	GLfloat			frameTime;

	__declspec(dllexport) Tile(GLuint palette = 0, GLfloat page = 0.0f, GLfloat tilex = 0.0f, GLfloat tiley = 0.0f, GLint lastframe = 1, GLfloat frametime = 5);
	__declspec(dllexport) Tile(const Tile &);
	__declspec(dllexport) ~Tile();
	__declspec(dllexport)  init(GLuint palette = 0, GLfloat page = 0.0f, GLfloat tilex = 0.0f, GLfloat tiley = 0.0f, GLint lastframe = 1, GLfloat frametime = 5);
	__declspec(dllexport)  const Tile &operator=(const Tile &);
	__declspec(dllexport)  bool operator==(const Tile &) const;
	__declspec(dllexport)  bool operator<(const Tile &) const;
	__declspec(dllexport)  bool operator>(const Tile &) const;
	__declspec(dllexport)  bool operator*(const Tile &) const;
	__declspec(dllexport)  void update();
	__declspec(dllexport)  void print() const;
};
#endif


