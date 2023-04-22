#pragma once
#include "stdafx.h"

#ifndef TILE_H
#define TILE_H

class Tile : public GraphicElement
{
	public:
	GLuint	firstFrame;
	GLuint	lastFrame;
	GLuint	actualFrame;
	GLuint	frameCounter;
	GLuint	frameTime;

	__declspec(dllexport) Tile(GLuint palette = 0, GLuint page = 0, GLuint tilex = 0, GLuint tiley = 0, GLuint tilewidth = 16, GLuint tileheight = 16, GLuint lastframe = 1, GLuint frametime = 0);
	__declspec(dllexport) Tile(const Tile &);
	__declspec(dllexport) ~Tile();
	__declspec(dllexport)  init(GLuint palette = 0, GLuint page = 0, GLuint tilex = 0, GLuint tiley = 0, GLuint tilewidth = 16, GLuint tileheight = 16, GLuint lastframe = 1, GLuint frametime = 0);
	__declspec(dllexport)  const Tile &operator=(const Tile &);
	__declspec(dllexport)  bool operator==(const Tile &) const;
	__declspec(dllexport)  bool operator<(const Tile &) const;
	__declspec(dllexport)  bool operator>(const Tile &) const;
	__declspec(dllexport)  bool operator*(const Tile &) const;
	__declspec(dllexport)  void update();
	__declspec(dllexport)  void print() const;
};
#endif


