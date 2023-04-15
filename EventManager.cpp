#include "EventManager.h"

EventManager::EventManager()
{
    ptrEvents = nullptr;
}

EventManager::~EventManager()
{

}

void EventManager::checkEvents()
{
	while (SDL_PollEvent(ptrEvents))
	{
         switch (ptrEvents->key.type)
        {
                case SDL_KEYDOWN:
                {
                    switch (ptrEvents->key.keysym.sym)
                    {
                        case SDLK_ESCAPE:

                            break;

                      }
                }

            case SDL_KEYUP:
            {
                switch (ptrEvents->key.keysym.sym)
                {
                  case SDLK_ESCAPE:

                    break;
                }
            }
            break;

            default:
            break;
        }
    }
}


