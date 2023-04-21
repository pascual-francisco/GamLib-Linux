#pragma once
#include "stdafx.h"

Scene::Scene(GLuint id, bool act, GLfloat viewportX, GLfloat viewportY, GLfloat viewportW, GLfloat viewportH, GLuint program, GLuint type, GLfloat left, GLfloat right, GLfloat bottom,
GLfloat top, GLfloat znear, GLfloat zfar, GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ, GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
	sceneID = id;
	active = act;
	programID = program;
	viewPort.x = viewportX;
	viewPort.y = viewportY;
	viewPort.w = viewportW;
	viewPort.h = viewportH;

	projection = mat4(1.0f);
	view = mat4(1.0f);

	ptrObjects = nullptr;
	ptrBackground = nullptr;
	ptrForeground = nullptr;

	//Init Samplers
	int samplers[32];
	for (uint i = 0; i < 32; i++)
		samplers[i] = i;

	glUniform1iv(glGetUniformLocation(programID, "fSamplers"), 32, samplers);
    ptrCamera = new Camera(true, program, type, left, right, bottom, top, znear, zfar, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

Scene::~Scene()
{
    delete ptrCamera;
	delete ptrObjects;
	delete ptrBackground;
	delete ptrForeground;
}

void Scene::update()
{
	if (ptrBackground != nullptr)
	{
		updateBackground();
		ptrBackground->update();
		ptrBackground->batchDraw();
	}

	if (ptrObjects != nullptr)
	{
		updateObjects();
		ptrObjects->update();
		ptrObjects->batchDraw();
	}

	if (ptrForeground != nullptr)
	{
		updateForeground();
		ptrForeground->update();
		ptrForeground->batchDraw();
	}
}

void Scene::print() const
{
	if(ptrObjects != nullptr)
		ptrObjects->print();

	if(ptrBackground != nullptr)
		ptrBackground->print();

	if(ptrForeground != nullptr)
		ptrForeground->print();

	if(ptrCamera != nullptr)
		ptrCamera->print();

}
