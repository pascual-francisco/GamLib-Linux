#include "stdafx.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity: public GameObject
{
	public:
	Mechanics		mechanics;
	stack < FSMState * > 	brain;
	vector<Track *>		tracks;
	vector<Sprite *>	sprite;
	static uint		maxInstances;
	static uint		instances;


	  Entity();
	  Entity(const Entity &);
	  ~Entity();

	  virtual const Entity &operator=(const Entity &);
	  virtual bool operator==(const Entity &) const;
	  virtual bool operator<(const Entity &) const;
	  virtual bool operator>(const Entity &) const;
	  virtual void update();
	  virtual void print() const;
};
#endif



