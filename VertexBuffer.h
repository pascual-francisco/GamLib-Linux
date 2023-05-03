
#include "stdafx.h"

#ifndef VERTEXBUFFER_H
#define	VERTEXBUFFER_H

class VertexBuffer: public BufferObject
{
	private:


	public:
	  VertexBuffer(GLuint count, GLintptr size, const void *data);
	  ~VertexBuffer();


	  void update(GLintptr offset, GLintptr size, const void *data);
	  void attach();
	  void detach();
	  void print() const;
};
#endif // !VERTEXBUFFER_H


