#pragma once
#include "stdafx.h"

#ifndef RENDERBUFFER_H
#define	RENDERBUFFER_H

class RenderBuffer : public BufferObject
{
	private:


	public:
	GLenum	attachment;
	GLsizei	width;
	GLsizei	height;

	  RenderBuffer(GLenum  target, GLenum attachPoint, GLuint format, GLsizei w, GLsizei h);
	  ~RenderBuffer();
	   void update(GLintptr offset, GLintptr size, const void *data);
	   void attach();
	   void detach();
	   void print() const;
};
#endif // !RENDERBUFFER_H


