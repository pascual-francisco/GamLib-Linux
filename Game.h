#pragma once
#include "stdafx.h"

#ifndef GAME_H
#define GAME_H

class Game
{
	public:
	GLuint			actualScene;
	string			assetsPath;
	SDL_FRect		viewPort;
	bool			active;
	bool			debugMode;
	bool			upButton;
	bool			downButton;
	bool			rightButton;
	bool			leftButton;
	bool			startButton;
	bool			selectButton;
	bool			aButton;
	bool			bButton;
	bool			xButton;
	bool			yButton;
	bool			lButton;
	bool			rButton;
	SDL_Event		gameEvents;
	GLuint			joystickCount;
	SDL_Joystick	*ptrJoystick;
	Renderer		*ptrRenderer;
	TextureManager	*ptrTextureManager;
	SoundManager	*ptrSoundManager;
	vector<Scene *>  scenes;


	__declspec(dllexport) Game(bool mode, string file, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	__declspec(dllexport) ~Game();

	__declspec(dllexport) virtual void	initScenes() = 0;
	__declspec(dllexport) virtual void	initTextures() = 0;
	__declspec(dllexport) virtual void	initSounds() = 0;
	__declspec(dllexport) virtual void	initUniforms() = 0;
	__declspec(dllexport) virtual void	initBuffers() = 0;

	__declspec(dllexport) virtual void	update() = 0;
	__declspec(dllexport) virtual void	updateUniforms() = 0;
	__declspec(dllexport) virtual void	updateTextures() = 0;
	__declspec(dllexport) virtual void	updateSounds() = 0;
	__declspec(dllexport) virtual void	updateBuffers() = 0;
	__declspec(dllexport) virtual void	updateScene() = 0;
	__declspec(dllexport) virtual void	checkEvents() = 0;
};

#endif // !GAME_H

