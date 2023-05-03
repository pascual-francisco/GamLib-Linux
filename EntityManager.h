#include "stdafx.h"

#ifndef ENTITYMANAGER_H
#define	ENTITYMANAGER_H

class EntityManager
{
	private:
	  void checkCollisions(GLuint, GLuint);
	  void updateData(GLuint entity, GLuint sprite, GLuint offset);
	  void updatePosition(GLuint entity, GLuint sprite, GLuint offset);
	  void updateTexture(GLuint entity, GLuint sprite, GLuint offset);
	  void updateImage(GLuint entity, GLuint sprite, GLuint offset);
	  void updateColor(GLuint entity, GLuint sprite, GLuint offset);
	  void updatePivot(GLuint entity, GLuint sprite, GLuint offset);
	  void updateTranslate(GLuint entity, GLuint sprite, GLuint offset);
	  void updateScale(GLuint entity, GLuint sprite, GLuint offset);
	  void updateRotate(GLuint entity, GLuint sprite, GLuint offset);
	  void updateEntities();

	public:
	Entity	**entitiesArray;
	GLuint	entitiesArraySize;
	GLfloat	*dataArray;
	GLuint	dataArraySize;

	vector<Entity *> entities;
	vector<GLfloat *> data;


	  EntityManager(GLuint count = 1);
	  ~EntityManager();

	  void initDataArray();
	  void update();
	  void print() const;
};
#endif // !ENTITYMANAGER
