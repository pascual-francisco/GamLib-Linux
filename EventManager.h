#include "stdafx.h"

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

class EventManager
{
    public:
        SDL_Event* ptrEvents;
        EventManager();
        virtual ~EventManager();
        void checkEvents();

    protected:

    private:
};

#endif // EVENTMANAGER_H
