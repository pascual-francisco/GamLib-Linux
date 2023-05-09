#include "stdafx.h"

#ifndef TEXTUREBUFFER_H
#define	TEXTUREBUFFER_H

class TextureBuffer : public BufferObject
{
private:


	public:
	GLuint textureUnit;

	  TextureBuffer(GLuint count, GLintptr size, const void *data, GLuint format, GLuint unit);
	  ~TextureBuffer();
	   void update(GLintptr offset, GLintptr size, const void *data);
	   void attach() ;
	   void detach() ;
	   void print() const;

};
#endif // !TEXTUREBUFFER_H



