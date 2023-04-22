#pragma once
#include "stdafx.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite: public GraphicElement
{
	public:
	vec2		positionOffset;
	Animation	*ptrAnimation;

	__declspec(dllexport) Sprite(GLuint palette = 0, GLuint page = 0);
	__declspec(dllexport) Sprite(const Sprite &);
	__declspec(dllexport) ~Sprite();
	__declspec(dllexport) void init(GLuint palette = 0, GLuint page = 0);
	__declspec(dllexport) const Sprite &operator=(const Sprite &);
	__declspec(dllexport) bool operator==(const Sprite &) const;
	__declspec(dllexport) bool operator<(const Sprite &) const;
	__declspec(dllexport) bool operator>(const Sprite &) const;
	__declspec(dllexport) bool operator*( Sprite &) ;
	__declspec(dllexport) void virtual update();
	__declspec(dllexport) void print() const;
};

#endif // !SPRITE_H

