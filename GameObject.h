#include "stdafx.h"

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

class GameObject
{
	public:
	string		name;
	bool		active;
	uint		healthPoints;
	uint		attackDamage;
	uint		weakness;
	float		direction;

	  GameObject()
	{
		name = "name";
		active = false;
		healthPoints = 0;
		attackDamage = 0;
		weakness = 0;
	};

	  GameObject(const GameObject &object)
	{
		name = object.name;
		active = object.active;
		healthPoints = object.healthPoints;
		attackDamage = object.attackDamage;
		weakness = object.weakness;
	}

	  ~GameObject(){};

	   virtual void update() = 0;
	   virtual void print() const = 0;
};
#endif // !GAMEOBJECT_H
