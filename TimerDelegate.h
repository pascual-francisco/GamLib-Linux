#include "stdafx.h"

	#ifndef TIMERDELEGATE_H
	#define TIMERDELEGATE_H

	class TimerDelegate
	{
		public:
		  TimerDelegate();
		  ~TimerDelegate();
		  virtual void onTick();
	};
	#endif
