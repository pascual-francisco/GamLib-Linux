#pragma once
#include "stdafx.h"

#ifndef FSMSTATE_H
#define	FSMSTATE_H

class FSMState
{
	public:
	string name;
	GLfloat time;
	GLfloat counter;

	  FSMState()
	{
		name = "";
		time = 0.0f;
		counter = 0.0f;
	};
	  ~FSMState() {};

	  virtual void enter() = 0;
	  virtual void exit() = 0;
	  virtual void update() = 0;

	  void print() const
	{

		cout << "State Name = " << name << endl;
		cout << "State Time = " << time << endl;
		cout << "State Counter = " << counter << endl;
	};
};
#endif // !STATE_H
