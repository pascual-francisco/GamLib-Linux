#include "stdafx.h"

Game::Game(string name, bool mode, string file, GLfloat w, GLfloat h)
{
	active = true;
	actualScene = 0;
	assetsPath = file;
	gameName = name;
	viewPort.x = 0.0f;
	viewPort.y = 0.0f;
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
	ptrCamera = nullptr;
   ptrRenderer = new Renderer(name, mode, file, w, h);

}

Game::~Game()
{
	delete ptrRenderer;
	delete ptrTextureManager;
	delete ptrSoundManager;
    delete ptrJoystick;
}
