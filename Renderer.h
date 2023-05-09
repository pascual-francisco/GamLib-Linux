#include "stdafx.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
	public:
	bool			   active;
	bool			   debugMode;
	ofstream		   logFile;
	string			assetsPath;
	SDL_Rect		   viewPort;
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

    Renderer(bool mode = true, string path = "Assets/Shaders/" , GLuint shadersQuantity = 1,  GLuint x = 0, GLuint y = 0, GLuint w = 256, GLuint h = 224);
	~Renderer();

	virtual void	initGlobals();
	virtual void	initSDL();
	virtual void	initOpenGL();
	virtual void	initGlew();
	virtual void	initShaders(string vertex = "texRect.vp", string fragment = "textRect.fp");
	virtual void	update();
	virtual void	checkErrors();

	static	GLfloat COSTABLE[360];
	static  GLfloat SINTABLE[360];
	static  GLfloat TANTABLE[360];
	static  GLfloat ACOSTABLE[360];
	static  GLfloat ASINTABLE[360];
	static  GLfloat ATANTABLE[360];

	void print() const;
};

#endif // !RENDERER_H
