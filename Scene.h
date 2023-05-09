#include "stdafx.h"

#ifndef SCENE_H
#define	SCENE_H

class Scene
{
	public:
	bool			active;
	GLuint			sceneID;
	GLuint			programID;
	SDL_FRect		viewPort;
	ObjectManager	*ptrObjects;
	TileMapManager	*ptrBackground;
	TileMapManager	*ptrForeground;
	Camera          *ptrCamera;

    Scene(GLuint id = 0, bool act = true,
    GLfloat viewportX = 0.0f, GLfloat viewportY = 0.0f, GLfloat viewportW = 256.0f, GLfloat viewportH = 224.0f,
	GLuint program = 0, GLuint type = 0, GLfloat left = 0.0f, GLfloat right = 256.0f, GLfloat bottom = 0.0f, GLfloat top = 240.0f,
    GLfloat near = 1000.0f , GLfloat far = -1000.0f, GLfloat eyeX = 0.0f, GLfloat eyeY = 0.0f, GLfloat eyeZ = 0.0f,
    GLfloat centerX = 0.0f , GLfloat centerY = 0.0f , GLfloat centerZ = -1.0f,
    GLfloat upX = 0.0f, GLfloat upY = 1.0f, GLfloat upZ = 0.0f);

    virtual ~Scene();

    virtual void	initObjects()  = 0;
    virtual void	initBackground() = 0;
    virtual void	initForeground() = 0;

    void update();
    virtual void	updateObjects()  = 0;
    virtual void	updateBackground()  = 0;
    virtual void	updateForeground()  = 0;
    void print() const;

};
#endif// !SCENE_H
