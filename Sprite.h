#pragma once
#include "stdafx.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite : public GraphicElement
{
	public:
	GLuint		textureUnit;
	GLuint		textureID;			
	vector<HitBox *>hitBox;
	vec2		positionOffset;
	vec4		textureOffset;
	vec4		color[4];
	bool		active;
	
	GLuint		animationState;
	GLint		firstFrame;
	GLint		lastFrame;
	GLint		actualFrame;
	GLfloat		frameCounter;
	GLfloat		frameTime;
	GLuint		loopCounter;
	bool		loop;	

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
	
	__declspec(dllexport) Sprite(GLuint id = 0, GLint ff = 0, GLint lf = 1, GLint af = 0, GLfloat ft = 0, GLuint s = 0);
	__declspec(dllexport) Sprite(const Sprite &);
	__declspec(dllexport) ~Sprite();

	__declspec(dllexport) void init(GLuint id = 0, GLint ff = 0, GLint lf = 1, GLint af = 0, GLfloat ft = 0, GLuint s = 0);
	__declspec(dllexport) const Sprite &operator=(const Sprite &);
	__declspec(dllexport) void setAnimation(GLint ff, GLint lf, GLint af, GLfloat ft, GLuint s);
	__declspec(dllexport) bool operator==(const Sprite &) const;
	__declspec(dllexport) bool operator<(const Sprite &) const;
	__declspec(dllexport) bool operator>(const Sprite &) const;
	__declspec(dllexport) bool operator*( Sprite &) ;
	__declspec(dllexport)  void update();
	__declspec(dllexport)  void print() const;
};

#endif // !SPRITE_H

