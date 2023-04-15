#pragma once
#include "stdafx.h"

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class TextureManager
{
	public:
	__declspec(dllexport)		TextureManager();
	__declspec(dllexport)		~TextureManager();
	__declspec(dllexport) void	initTexture(GLuint name, string path, GLuint quantity, GLuint target);
	__declspec(dllexport) void print() const;
};
#endif // !TEXTUREMANAGER_H
