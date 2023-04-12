#pragma once
#include "stdafx.h"

#ifndef ENTITYMANAGER_H
#define	ENTITYMANAGER_H

class EntityManager
{
	private:		
	__declspec(dllexport) void checkCollisions(GLuint, GLuint);
	__declspec(dllexport) void updateData(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updatePosition(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updateTexture(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updateImage(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updateColor(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updatePivot(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updateTranslate(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updateScale(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updateRotate(GLuint entity, GLuint sprite, GLuint offset);
	__declspec(dllexport) void updateEntities();

	public:
	Entity	**entitiesArray;
	GLuint	entitiesArraySize;	
	GLfloat	*dataArray;
	GLuint	dataArraySize;		

	vector<Entity *> entities;
	vector<GLfloat *> data;

	
	__declspec(dllexport) EntityManager(GLuint count = 1);
	__declspec(dllexport) ~EntityManager();
	
	__declspec(dllexport) void initDataArray();
	__declspec(dllexport) void update();
	__declspec(dllexport) void print() const;
};
#endif // !ENTITYMANAGER
