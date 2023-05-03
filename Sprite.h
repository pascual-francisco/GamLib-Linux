#include "stdafx.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite: public GraphicElement
{
	public:
	vec2		positionOffset;
	Animation	*ptrAnimation;

	  Sprite(GLuint palette = 0, GLuint page = 0);
	  Sprite(const Sprite &);
	  ~Sprite();
	  void init(GLuint palette = 0, GLuint page = 0);
	  const Sprite &operator=(const Sprite &);
	  bool operator==(const Sprite &) const;
	  bool operator<(const Sprite &) const;
	  bool operator>(const Sprite &) const;
	  bool operator*( Sprite &) ;
	  void virtual update();
	  void print() const;
};

#endif // !SPRITE_H

