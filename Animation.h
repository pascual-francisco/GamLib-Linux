#pragma once
#include "stdafx.h"

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
    public:
    GLuint			animationState;
	GLint			firstFrame;
	GLint			lastFrame;
	GLint			actualFrame;
	GLfloat			frameCounter;
	GLfloat			frameTime;
	GLuint			loopCounter;
	bool			loop;

	enum AnimationStates
	{
		FORWARD = 0,
		BACKWARD,
		LOOP_FORWARD,
		LOOP_BACKWARD,
		FORWARD_BACKWARD,
		PAUSE,
		STOP
	};

	  Animation(GLint firstframe = 0, GLint lastfframe = 1, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = 0);
   	  Animation(const Animation &);
   	   ~Animation();

	  void init(GLint firstframe = 0, GLint lastfframe = 1, GLint actualframe = 0, GLfloat frametime = 0, GLuint actualstate = 0);
      void update();
      void print() const;

	  const Animation &operator=(const Animation &);
      bool operator==(const Animation &) const;
	  bool operator<(const Animation &) const;
	  bool operator>(const Animation &) const;
	  bool operator*( Animation &) ;
    };

#endif // ANIMATION_H

