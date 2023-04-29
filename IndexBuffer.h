#pragma once
#include "stdafx.h"

#ifndef INDEXBUFFER_H
#define	INDEXBUFFER_H

class IndexBuffer: public BufferObject
{
	public:
	  IndexBuffer(GLuint count, GLintptr size, const void *data);
	  ~IndexBuffer();

	  void update(GLintptr offset, GLintptr size, const void *data);
	  void attach() ;
	  void detach() ;
	  void print() const;
};
#endif // !INDEXBUFFER_H
#pragma once
