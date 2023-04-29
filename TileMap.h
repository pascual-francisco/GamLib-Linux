#pragma once
#include "stdafx.h"

#ifndef TILEMAP_H
#define TILEMAP_H

class TileMap : public GameObject
{
	public:
	Mechanics		mechanics;	
	Sprite			*sprite;
	unsigned int	spriteSize;

	__declspec(dllexport) TileMap();

	__declspec(dllexport) ~TileMap();

	__declspec(dllexport) void init(bool, bool, GLuint, GLuint);
	__declspec(dllexport) virtual const TileMap &operator=(const TileMap &);
	__declspec(dllexport) virtual bool operator==(const TileMap &) const;
	__declspec(dllexport) virtual bool operator<(const TileMap &) const;
	__declspec(dllexport) virtual bool operator>(const TileMap &) const;
	__declspec(dllexport) void update();
	__declspec(dllexport) void print();
};
#endif // !TILEMAP_H
