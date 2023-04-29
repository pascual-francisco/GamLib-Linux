#pragma once
#include "stdafx.h"

#ifndef PACKBUFFER_H
#define	PACKBUFFER_H

class PackBuffer : public BufferObject
{
private:



public:


	  PackBuffer(GLuint count, GLintptr size, const void *data);
	  ~PackBuffer();

	   void update(GLintptr offset, GLintptr size, const void *data);
	   void attach() ;
	   void detach() ;
	   void print() const;
};
#endif // !PACKBUFFER_H



