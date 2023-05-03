
#include "stdafx.h"

#ifndef	UNIFORMBUFFER_H
#define	UNIFORMBUFFER_H

class UniformBuffer: public BufferObject
{
public:
	const GLchar	**names;
	const void		*data;
	GLsizei			dataSize;
	GLuint			shaderProgramID;
	GLuint			uniformBufferID;
	GLuint			blockSize;
	GLuint			blockIndex;
	GLuint			*offsets;
	GLuint			*indices;
	GLuint			*sizes;
	GLsizei			memberCount;

public:
	  UniformBuffer();
	  UniformBuffer(GLuint program, GLsizei count,       const void *data, GLsizei size);
	  ~UniformBuffer();
	  void init(GLuint program, GLsizei count, const void *data, GLsizei size);
	  void initUniformIndices();
	  void initUniformLocations();
	  void attach() const;
	  void detach() const;
};
#endif // !VERTEXBUFFER_H
#pragma once
