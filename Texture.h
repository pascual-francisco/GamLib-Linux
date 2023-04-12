#pragma once
#include "stdafx.h"

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	private:
	__declspec(dllexport) void init(string name, string path, GLuint width, GLuint height, GLuint depth, GLenum target, GLuint unit, GLenum internalFormat, GLenum format, GLenum type);
	__declspec(dllexport) void reserveImage3D();
	__declspec(dllexport) void loadImage3D();
	__declspec(dllexport) void reserveImage2D();
	__declspec(dllexport) void loadImage2D();

	
	public:
	string	textureName;	
	GLuint	textureID;
	string	texturePath;
	GLsizei textureWidth;
	GLsizei textureHeight;
	GLsizei textureDepth;
	GLuint	textureUnit;
	GLenum	textureTarget;
	GLenum	textureDataFormat;
	GLenum	textureInternalDataFormat;
	GLenum	textureDataType;	

	__declspec(dllexport) Texture(string name, string path, GLuint width, GLuint height, GLuint depth, GLenum target, GLuint unit, GLenum internalFormat, GLenum format, GLenum type);
	__declspec(dllexport) Texture(Texture&);
	__declspec(dllexport) ~Texture();

	__declspec(dllexport) const Texture &operator=(const Texture &);
	__declspec(dllexport) bool operator==(const Texture &) const;
	__declspec(dllexport) bool operator<(const Texture &) const;
	__declspec(dllexport) bool operator>(const Texture &) const;
	
	__declspec(dllexport) void attach(GLuint unit);
	__declspec(dllexport) void detach() const;
	__declspec(dllexport) void print() const;
};
#endif