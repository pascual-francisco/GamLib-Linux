#include "stdafx.h"

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

class FrameBuffer : public BufferObject
{
	private:

	public:
		GLuint attachmentPoints[18];
		string frameBufferStatus;

	  FrameBuffer(GLuint target);
	  ~FrameBuffer();


	   void update(GLintptr offset, GLintptr size, const void *data);
	   void attach();
	   void attachRenderBuffer(RenderBuffer* buffer);
	   void attachColor(GLuint point, GLuint buffer);
	   void attachDepth(GLuint buffer);
	   void attachStencil(GLuint buffer);
	   void attachTexture(GLuint buffer);
	   void attachDraw();
	   void attachRead();
	   void checkStatus();

	   void detachPoints();
	   void detach();
	   void print() const;

};
#endif // !FRAMEBUFFER_H



