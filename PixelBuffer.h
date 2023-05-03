#include "stdafx.h"

#ifndef PIXELBUFFER_H
#define	PIXELBUFFER_H

class PixelBuffer : public BufferObject
{
private:


	public:
	  PixelBuffer(GLuint count, GLintptr size, const void *data, GLenum target);
	  ~PixelBuffer();

	   void update(GLintptr offset, GLintptr size, const void *data);
	   void attach() ;
	   void detach() ;
	   void print() const;

	   void attachPack();
	   void attachUnpack();

};
#endif // !PIXELBUFFER_H



