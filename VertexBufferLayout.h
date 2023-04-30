#pragma once
#include "stdafx.h"

#ifndef VERTEXBUFFERLAYOUT_H
#define	VERTEXBUFFERLAYOUT_H

class VertexBufferLayout
{
	public:
	GLuint			strideSize;
	GLuint			count;
	GLuint			dataType;
	GLboolean		normalize;
	GLuint			attributeLocation;
	const GLchar	*attributeName;
	GLuint			shaderProgramID;

	public:
		  VertexBufferLayout();
		  VertexBufferLayout(GLuint shaderProgramID, const GLchar *attributeName, GLuint count, GLboolean normalize, GLuint strideSize, GLuint offset);
		  ~VertexBufferLayout();

		  void attach();
		  void dettach();
		  void print() const;

};

#endif // !VERTEXBUFFERLAYOUT_H
