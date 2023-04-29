#include "stdafx.h"


	#ifndef TIMER_H
	#define TIMER_H

	class Timer
	{
		public:
		long int inTime;
		long int  outTime;
		long int  frameTime;
		long int  frequency;
		uint actualFrame;
		uint frameRate;
		list<TimerDelegate*> timerDelegate;

		  Timer(unsigned int = 30);
		  ~Timer();
		  void update();
	};
	#endif

