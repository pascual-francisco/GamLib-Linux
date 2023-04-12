#pragma once
#include "stdafx.h"

#ifndef TILE_H
#define TILE_H

class Tile : public GraphicElement
{
public:
	Mechanics		mechanics;	
	Sprite			*sprite;
	unsigned int	spriteSize;

	__declspec(dllexport) Tile();
	__declspec(dllexport) Tile(const Tile &);
	__declspec(dllexport) ~Tile();

	__declspec(dllexport) virtual const Tile &operator=(const Tile &);
	__declspec(dllexport) virtual bool operator==(const Tile &) const;
	__declspec(dllexport) virtual bool operator<(const Tile &) const;
	__declspec(dllexport) virtual bool operator>(const Tile &) const;
	__declspec(dllexport) virtual bool operator*(const Tile &) const;
	__declspec(dllexport) virtual void update();
	__declspec(dllexport) virtual void print() const;
};
#endif


