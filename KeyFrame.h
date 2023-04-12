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

		__declspec(dllexport) KeyFrame(int keyTime = 0, float keyValue = 0,  int easingF = 0,  int easingR = 0, bool actionActive = false,  int actionState = 0,  int fireDirection = 0,  int time = 0,  int key = 0);				
		__declspec(dllexport) KeyFrame(const KeyFrame& key);
		__declspec(dllexport) ~KeyFrame();

		__declspec(dllexport) void reset();
		__declspec(dllexport) const KeyFrame& operator=(const KeyFrame& key);
		__declspec(dllexport) bool operator==(const KeyFrame& key) const;
		__declspec(dllexport) bool operator<(const KeyFrame& key) const;
		__declspec(dllexport) bool operator>(const KeyFrame& key) const;
	};
	#endif