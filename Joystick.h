#include "stdafx.h"

#ifndef JOYSTICK_H
#define JOYSTICK_H


class Joystick
{
    public:
        bool    active;
        bool	upButton;
        bool	downButton;
        bool	rightButton;
        bool	leftButton;
        bool	startButton;
        bool	selectButton;
        bool	aButton;
        bool	bButton;
        bool	xButton;
        bool	yButton;
        bool	lButton;
        bool	rButton;
        SDL_Joystick* ptrJoystick;

        Joystick();
        virtual ~Joystick();
        Joystick(const Joystick& other);

    protected:

    private:

};

#endif // JOYSTICK_H
