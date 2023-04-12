#include "stdafx.h"

HitBox::HitBox()
{
	box.x = 0.0f;
	box.y = 0.0f;
	box.w = 0.0f;
	box.h = 0.0f;
	left = -1;
	right = -1;
	up = -1;
	down = -1;
}

HitBox::HitBox(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	init(x, y, w, h);
}

HitBox::HitBox(const HitBox &object)
{
	if (&object != this)
	{
		box = object.box;
		left = object.left;
		right = object.right;
		up = object.up;
		down = object.down;
	}
}

HitBox::~HitBox()
{

}

void HitBox::init(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	left = -1;
	right = -1;
	up = -1;
	down = -1;
}

const HitBox &HitBox::operator=(const HitBox &object)
{
	if (&object != this)
	{
		box.x = object.box.x;
		box.y = object.box.y;
		box.w = object.box.w;
		box.h = object.box.h;
		left = object.left;
		right = object.right;
		up = object.up;
		down = object.down;
	}
	return *this;
}

const HitBox &HitBox::operator+(const HitBox &)
{
	// TODO: insert return statement here
}

const HitBox &HitBox::operator-(const HitBox &)
{
	// TODO: insert return statement here
}

bool HitBox::operator==(const HitBox &object) const
{
	if (&object != this)
	{
		if (box.x == object.box.x &&
			box.y == object.box.y &&
			box.w == object.box.w &&
			box.h == object.box.h &&
			left == object.left &&
			right == object.right &&
			up == object.up &&
			down == object.down
			)
	
		return true;
	else
		return false;
	}
	else
		return false;
}

bool HitBox::operator<(const HitBox &object) const
{
	if (box.w < object.box.w && box.h < object.box.h)
		return true;	
	else
		return false;
}

bool HitBox::operator>(const HitBox &object) const
{
	if (box.w > object.box.w && box.h > object.box.h)
		return true;
	else
		return false;
}

bool HitBox::operator*(const HitBox &object) const
{
	SDL_Rect A;
	SDL_Rect B;
	
	A.x = box.x;
	A.y = box.y;
	A.w = box.w;
	A.h = box.h;

	B.x = object.box.x;
	B.y = object.box.y;
	B.w = object.box.w;
	B.h = object.box.h;

	return SDL_HasIntersection(&A, &B);		
}

void HitBox::reset()
{
	left = -1;
	right = -1;
	up = -1;
	down = -1;
}

void HitBox::print() const
{
	cout << "Hit Box Info [" << 0 << "] = " << "[" << box.x << ", " << box.y << ", " << box.w << ", " << box.h << "]" << endl;
	cout << "Right = " << right << endl;
	cout << "Left = " << left << endl;
	cout << "Up = " << up << endl;
	cout << "Down = " << down << endl;
	
}
