#pragma once
#include "stdafx.h"

#ifndef HITBOX_H
#define HITBOX_H

class HitBox
{
	public:
	SDL_FRect box;
	GLint left;
	GLint right;
	GLint up;
	GLint down;

	__declspec(dllexport) HitBox();
	__declspec(dllexport) HitBox(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	__declspec(dllexport) HitBox(const HitBox &);
	__declspec(dllexport)~HitBox();	
	__declspec(dllexport) void init(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	__declspec(dllexport) const HitBox &operator=(const HitBox &);	
	__declspec(dllexport) const HitBox &operator+(const HitBox &);
	__declspec(dllexport) const HitBox &operator-(const HitBox &);
	__declspec(dllexport) bool operator==(const HitBox &) const;
	__declspec(dllexport) bool operator<(const HitBox &) const;
	__declspec(dllexport) bool operator>(const HitBox &) const;
	__declspec(dllexport) bool operator*(const HitBox &) const;
	__declspec(dllexport) void reset();	
	__declspec(dllexport) void print() const;
};

#endif // !HITBOX_H



