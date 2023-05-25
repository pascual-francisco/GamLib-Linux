#include "stdafx.h"

#ifndef GAME_H
#define GAME_H

class Game
{
	public:
	GLuint			actualScene;
	string			assetsPath;
	string         gameName;
	SDL_FRect		viewPort;
	bool			   active;
	bool			   debugMode;
	bool			   upButton;
	bool			   downButton;
	bool			   rightButton;
	bool			   leftButton;
	bool			   startButton;
	bool			   selectButton;
	bool			   aButton;
	bool			   bButton;
	bool			   xButton;
	bool			   yButton;
	bool			   lButton;
	bool			   rButton;
	SDL_Event		gameEvents;
	GLuint			joystickCount;
	SDL_Joystick   *ptrJoystick;
	Renderer		   *ptrRenderer;
	TextureManager	*ptrTextureManager;
	SoundManager	*ptrSoundManager;
	Camera         *ptrCamera;
	vector<Scene *> scenes;

    Game(string name, bool mode, string file, GLfloat w, GLfloat h);
    ~Game();

    virtual void	initScenes() = 0;
    virtual void	initTextures() = 0;
    virtual void	initSounds() = 0;
    virtual void	initUniforms() = 0;
    virtual void	initBuffers() = 0;

    virtual void	update() = 0;
    virtual void	updateUniforms() = 0;
    virtual void	updateTextures() = 0;
    virtual void	updateSounds() = 0;
    virtual void	updateBuffers() = 0;
    virtual void	updateScene() = 0;
    virtual void	checkEvents() = 0;
};

#endif // !GAME_H

