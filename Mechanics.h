#pragma once
#include "stdafx.h"

#ifndef MECHANICS_H
#define	MECHANICS_H

class Mechanics
{
public:

	vec3	position;
	vec3	speed;
	vec3	maxSpeed;
	vec3	acceleration;

	GLfloat	mass;
	vec3	momentum;
	vec3	inertia;
	vec3	friction;
	vec3	gravity;

	  Mechanics();
	  Mechanics(const Mechanics &);
	  ~Mechanics();

	 	const Mechanics &operator=(const Mechanics &);
	 	bool operator==(const Mechanics &) const;
	 	bool operator<(const Mechanics &) const;
	 	bool operator>(const Mechanics &) const;
	 	bool operator*(const Mechanics &) const;
	 	void update();
	 	void print() const;
};

#endif // !MECHANICS_H
