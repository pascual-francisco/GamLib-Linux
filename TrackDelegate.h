    #include "stdafx.h"

	#ifndef TRACKDELEGATE_H
	#define TRACKDELEGATE_H

	class TrackDelegate
	{
		public:
        TrackDelegate();
        virtual ~TrackDelegate();
		virtual void onHeadPositionChangedForward( int);
		virtual void onHeadPositionChangedBackward( int);
		virtual void onHeadPositionChanged( int);
		virtual void onValueChanged(float);
		virtual void onValueChangedToZero();
		virtual void onValueChangedToOne();
		virtual void onFirstFrame();
		virtual void onLastFrame();
		virtual void onForward();
		virtual void onBackward();
		virtual void onLoopForward();
		virtual void onLoopBackward();
		virtual void onStop();
		virtual void onPause();
		virtual void onDirectionChanged( int);
		virtual void onStateChanged( int);
		virtual void onKeyFrame( int);
	};
	#endif
