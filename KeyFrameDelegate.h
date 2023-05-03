    #include "stdafx.h"

	#ifndef KEYFRAMEDELEGATE_H
	#define KEYFRAMEDELEGATE_H

	class KeyFrameDelegate
	{
		public:
		  KeyFrameDelegate();
		  virtual ~KeyFrameDelegate();
		  virtual void onForward();
		  virtual void onBackward();
		  virtual void onLoopForward();
		  virtual void onLoopBackward();
	};
	#endif
