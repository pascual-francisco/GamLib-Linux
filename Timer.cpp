#include "stdafx.h"

	Timer::Timer(unsigned int fr)
	{
		frameRate = (fr>0?fr:0);
		actualFrame = 0;
		ZeroMemory(&inTime,sizeof(LARGE_INTEGER));
		ZeroMemory(&outTime,sizeof(LARGE_INTEGER));
		ZeroMemory(&frameTime,sizeof(LARGE_INTEGER));
		ZeroMemory(&frequency,sizeof(LARGE_INTEGER));
		QueryPerformanceFrequency(&frequency);
	}

	Timer::~Timer()
	{

	}
	
	void Timer::update()
	{  		
		QueryPerformanceCounter(&outTime);
			
		if(outTime.QuadPart > inTime.QuadPart)
		{
			frameTime.QuadPart += (outTime.QuadPart - inTime.QuadPart) / frequency.QuadPart;
		}
		
		if(float(frameTime.QuadPart) >= (1/frameRate))
		{
			ZeroMemory(&frameTime,sizeof(LARGE_INTEGER));
			ZeroMemory(&inTime,sizeof(LARGE_INTEGER));
			ZeroMemory(&outTime,sizeof(LARGE_INTEGER));		

			if(actualFrame < frameRate)
			{
				actualFrame++;
			}
			else
			{
				actualFrame = 0;
			}

			list<TimerDelegate*>::iterator it;		
			if(timerDelegate.size() > 0)
			{
				for(it = timerDelegate.begin(); it !=  timerDelegate.end(); it++)
				{
					if((*it)!=NULL)
					{
						(*it)->onTick();
					}
				}
			}
		}	
		QueryPerformanceCounter(&inTime);
	}


