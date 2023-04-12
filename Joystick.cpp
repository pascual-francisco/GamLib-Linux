#include "Joystick.h"

Joystick::Joystick()
{
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
}

Joystick::~Joystick()
{
     if (ptrJoystick != nullptr)
     {
         delete ptrJoystick;
     }
}

Joystick::Joystick(const Joystick& other)
{
    //copy ctor
}
