#pragma once
#include "stdafx.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
	public:
	bool			active;
	bool			debugMode;
	ofstream		logFile;
	string			assetsPath;
	SDL_Rect		viewPort;
	GLfloat			FPS;
	GLfloat			actualFrame;
	SDL_GLContext	ptrGLContext;
	SDL_Window		*ptrWindow;
	FrameBuffer		**ptrFrameBuffers;
	RenderBuffer	**ptrRenderBuffers;
	PixelBuffer		**ptrPixelBuffer;
	TextureManager	*ptrTextureManager;
	TextureBuffer	*ptrTextureBuffer;
	Shader			**ptrShaders;

	vector<Shader *> shaders;
	vector<string>  shaderNames;

	 				Renderer(bool mode, string file, GLuint x, GLuint y, GLuint w, GLuint h);
	 				~Renderer();
	  virtual void	initGlobals();
	  virtual void	initSDL();
	  virtual void	initOpenGL();
	  virtual void	initGlew();
	  virtual void	initShaders();
	  virtual void	update();
	  virtual void	checkErrors();


	static	GLfloat COSTABLE[360];
	static  GLfloat SINTABLE[360];
	static  GLfloat TANTABLE[360];
	static  GLfloat ACOSTABLE[360];
	static  GLfloat ASINTABLE[360];
	static  GLfloat ATANTABLE[360];
};

#endif // !RENDERER_H
