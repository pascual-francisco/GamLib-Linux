#include "stdafx.h"

Game::Game(bool mode, string file, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	active = true;
	actualScene = 0;
	assetsPath = file;
	viewPort.x = x;
	viewPort.y = y;
	viewPort.w = w;
	viewPort.h = h;
	debugMode = mode;
	upButton = false;
	downButton = false;
	leftButton = false;
	rightButton = false;
	selectButton = false;
	startButton = false;
	aButton = false;
	bButton = false;
	yButton = false;
	xButton = false;
	lButton = false;
	rButton = false;
	ptrJoystick = nullptr;
    ptrRenderer = new Renderer(mode, file, x, y, w, h);
}

Game::~Game()
{
	delete ptrRenderer;
	delete ptrTextureManager;
	delete ptrSoundManager;
    delete ptrJoystick;
}
