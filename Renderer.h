#include "stdafx.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
	public:
	bool			      active;
	bool			      debugMode;
	ofstream		      logFile;
	string			   assetsPath;
	SDL_Rect		      viewPort;
	GLfloat			   FPS;
	GLfloat			   actualFrame;
	SDL_GLContext	   ptrGLContext;
	SDL_Window		   *ptrWindow;
	FrameBuffer		   **ptrFrameBuffers;
	RenderBuffer	   **ptrRenderBuffers;
	PixelBuffer		   **ptrPixelBuffer;
	TextureManager	   *ptrTextureManager;
	TextureBuffer	   *ptrTextureBuffer;
   vector<Shader *>  shaders;
   GLuint            actualShader;
   GLfloat           zoomFactor;
   string            gameName;

    Renderer(string name = "Game", bool mode = true, string path = "Assets/Shaders/", GLuint w = 256, GLuint h = 224, GLfloat z = 3.0f);
	~Renderer();

	virtual void	initGlobals();
	virtual void	initSDL();
	virtual void	initOpenGL();
	virtual void	initGlew();
	virtual void	initShader(string vertex = "texRect.vp", string fragment = "texRect.fp");
	virtual void   activateShader(GLuint index);
	virtual void	update();
	virtual void	checkErrors();

	static   GLfloat COSTABLE[360];
	static  GLfloat SINTABLE[360];
	static  GLfloat TANTABLE[360];
	static  GLfloat ACOSTABLE[360];
	static  GLfloat ASINTABLE[360];
	static  GLfloat ATANTABLE[360];

	void print() const;
};

#endif // !RENDERER_H
