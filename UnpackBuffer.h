
#include "stdafx.h"

#ifndef UNPACKBUFFER_H
#define	UNPACKBUFFER_H

class UnpackBuffer : public BufferObject
{
private:


public:
	  UnpackBuffer(GLuint count, GLintptr size, const void *data);
	  ~UnpackBuffer();

	   void update(GLintptr offset, GLintptr size, const void *data);
	   void attach();
	   void detach();
	   void print() const;
};
#endif // !UNPACKBUFFER_H
#pragma once


