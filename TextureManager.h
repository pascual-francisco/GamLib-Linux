#include "stdafx.h"

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class TextureManager
{
	public:
	 		TextureManager();
	 		~TextureManager();
	  void	initTexture(GLuint name, string path, GLuint quantity, GLuint target);
	  void print() const;
};
#endif // !TEXTUREMANAGER_H
