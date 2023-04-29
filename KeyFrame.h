#include "stdafx.h"
	#ifndef KEYFRAME_H
	#define KEYFRAME_H

	class KeyFrame
	{
		public:

		enum EasingMode
		{
			LINEAR, ACCELERATION,  DECELERATION, SMOOTHSTEP, DISCRETE
		};


		TrackAction	action;
		float	value;
		int	time;
		vector<KeyFrameDelegate*>	keyDelegate;

		 int	easingForward;
		 int	easingReverse;

		  KeyFrame(int keyTime = 0, float keyValue = 0,  int easingF = 0,  int easingR = 0, bool actionActive = false,  int actionState = 0,  int fireDirection = 0,  int time = 0,  int key = 0);
		  KeyFrame(const KeyFrame& key);
		  ~KeyFrame();

		  void reset();
		  const KeyFrame& operator=(const KeyFrame& key);
		  bool operator==(const KeyFrame& key) const;
		  bool operator<(const KeyFrame& key) const;
		  bool operator>(const KeyFrame& key) const;
	};
	#endif
