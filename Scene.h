#include "stdafx.h"

#ifndef SCENE_H
#define	SCENE_H

class Scene
{
	public:
	bool			   active;
	GLuint			sceneID;
	GLuint			programID;
   ObjectManager	*ptrObjects;
	TileMapManager	*ptrBackground;
	TileMapManager	*ptrForeground;

    Scene(GLuint id = 0, GLuint program = 3, bool act = true);
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
