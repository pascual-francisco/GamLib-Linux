    #include "stdafx.h"

	#ifndef TRACK_H
	#define TRACK_H

	class Track
	{
		private:
		KeyFrame				PK;
		KeyFrame				NK;
		float					derivative;
		float					timeDerivative;
		int						keyIndex;

		public:
		bool					loop;
		int						keys;
		vector<KeyFrame>		keyFrames;
		int						frames;
		int						head;
		float					value;
		float					time;
		bool					constant;
		vector<TrackDelegate*>	trackDelegate;
		int						frameTime;
		int						frameCounter;
		int						actualState;

		enum TrackStates
		{
			FORWARD,
			BACKWARD,
			PAUSE,
			STOP,
			PAUSE_FORWARD,
			PAUSE_BACKWARD,
			LOOP_FORWARD,
			LOOP_BACKWARD,
			GO_TO_KEY,
			GO_TO_KEY_FORWARD,
			GO_TO_KEY_BACKWARD,
			GO_TO_KEY_LOOP_FORWARD,
			GO_TO_KEY_LOOP_BACKWARD,
			GO_TO_KEY_STOP,
		};

        Track(int frames =0, int keys =0, int frameTime = 0, int state = 3, bool constant = false, float value = 0.0f);
        Track(const Track&);
        ~Track();
        const Track& operator=(const Track&);
        bool operator==(const Track&) const;
        bool operator<(const Track&) const;

        void updateEvent();
        void applyDerivative();
        void calculateDerivative();
        void forward();
        void backward();
        void pause();
        void stop();
        void goToKey(int key = 0);
        void goToKeyAndForward(int key = 0);
        void goToKeyAndBackward(int key = 0);
        void goToKeyAndStop(int key = 0);
        void goToFirstKey();
        void goToFirstKeyAndStop();
        void goToFirstKeyAndBackward();
        void goToFirstKeyAndForward();
        void goToLastKey();
        void goToLastKeyAndStop();
        void goToLastKeyAndBackward();
        void goToLastKeyAndForward();
        void update();
        void print() const;
	};
	#endif
