
#include "stdafx.h"

#ifndef VERTEXARRAY_H
#define	VERTEXARRAY_H

class VertexArray
{
public:
	GLuint	vertexArrayID;

public:
	  VertexArray();
	  ~VertexArray();

	  void init();
	  void attach() const;
	  void detach() const;
};
#endif // !VERTEXBUFFER_H
#pragma once
