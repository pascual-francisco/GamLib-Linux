#include "stdafx.h"

Scene::Scene(GLuint id, GLuint program, bool act)
{
	sceneID = id;
	active = act;
	ptrObjects = nullptr;
	ptrBackground = nullptr;
	ptrForeground = nullptr;
}

Scene::~Scene()
{
 	delete ptrObjects;
	delete ptrBackground;

	if(ptrForeground!=nullptr)
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
}
