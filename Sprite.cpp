#pragma once
#include "stdafx.h"

Sprite::Sprite(GLuint id, GLint ff, GLint lf, GLint af, GLfloat ft, GLuint s)
{
	init(id, ff, lf, af, ft, s);
}

Sprite::~Sprite()
{
}

Sprite::Sprite(const Sprite &object)
{
	if (&object != this)
	{
		active = object.active;
		positionOffset = object.positionOffset;
		textureUnit = object.textureUnit;
		transformation = object.transformation;
		textureOffset = object.textureOffset;
		texturePageOffset = object.texturePageOffset;
		hitBox = object.hitBox;
		color[0] = object.color[0];
		color[1] = object.color[1];
		color[2] = object.color[2];
		color[3] = object.color[3];
		animationState = 0;
		firstFrame = object.firstFrame;
		lastFrame = object.lastFrame;
		actualFrame = object.actualFrame;
		frameCounter = object.frameCounter;
		frameTime = object.frameTime;
		loopCounter = object.loopCounter;
		loop = object.loop;
	}
}

void Sprite::init(GLuint id, GLint ff, GLint lf, GLint af, GLfloat ft, GLuint s)
{
	GLint w = 0;
	GLint h = 0;
	GLint d = 0;

	active = true;
	textureUnit = 0;

	textureID = id;
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &w);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &h);
	glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_DEPTH, &d);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	setAnimation(ff, lf, af, ft, s);
	transformation.translate = vec3(0.0f, 0.0f, 0.0f);
	transformation.pivot = vec3(0.0f, 0.0f, 0.0f);
	transformation.rotate = vec3(0.0f, 0.0f, 0.0f);
	transformation.scale = vec3(1.0f, 1.0f, 1.0f);
	textureOffset = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	positionOffset = vec2(0.0f, 0.0f);
	texturePageOffset = 0.0f;

	for (uint i = 0; i < 4; i++)
	{
		color[i].r = 0.0f;
		color[i].g = 0.0f;
		color[i].b = 0.0f;
	}

	for (uint i = 0; i < 4; i++)
		color[i].a = 1.0f;
}

const Sprite &Sprite::operator=(const Sprite &object)
{
	if (&object != this)
	{
		active = object.active;
		textureID = object.textureID;
		positionOffset = object.positionOffset;
		textureUnit = object.textureUnit;
		transformation = object.transformation;
		hitBox = object.hitBox;
		textureOffset = object.textureOffset;
		texturePageOffset = object.texturePageOffset;
		color[0] = object.color[0];
		color[1] = object.color[1];
		color[2] = object.color[2];
		color[3] = object.color[3];
		animationState = object.animationState;
		firstFrame = object.firstFrame;
		lastFrame = object.lastFrame;
		actualFrame = object.actualFrame;
		frameCounter = object.frameCounter;
		frameTime = object.frameTime;
		loopCounter = object.loopCounter;
		loop = object.loop;

	}
	return *this;
}

void Sprite::setAnimation(GLint ff, GLint lf, GLint af, GLfloat ft, GLuint s)
{
	if (ff >= 0)
	{
		firstFrame = ff;
	}
	else
	{
		firstFrame = 0;
	}

	if (lf >= 0)
	{
		lastFrame = lf;
	}
	else
	{
		lastFrame = 0;
	}

	if (af >= firstFrame && af <= lastFrame)
	{
		actualFrame = af;
	}
	else
	{
		actualFrame = 0;
	}

	if (ft >= 0)
	{
		frameTime = ft;
	}
	else
	{
		frameTime = 0;
	}

	if (s >= Sprite::AnimationStates::FORWARD || s <= Sprite::AnimationStates::STOP)
	{
		animationState = s;
	}
	else
	{
		animationState = Sprite::AnimationStates::FORWARD;
	}
}

bool Sprite::operator ==(const Sprite &object) const
{
	if (&object != this)
	{
		if (
			active == object.active &&
			textureID == object.textureID &&
			positionOffset == object.positionOffset &&
			textureOffset == object.textureOffset &&
			texturePageOffset == object.texturePageOffset &&
			textureUnit == object.textureUnit &&
			hitBox == object.hitBox &&
			transformation.translate == object.transformation.translate &&
			transformation.rotate == object.transformation.rotate &&
			transformation.scale == object.transformation.scale &&
			color[0] == object.color[0] &&
			color[1] == object.color[1] &&
			color[2] == object.color[2] &&
			color[3] == object.color[3] &&
			animationState == object.animationState &&
			firstFrame == object.firstFrame &&
			lastFrame == object.lastFrame &&
			actualFrame == object.actualFrame &&
			frameCounter == object.frameCounter &&
			frameTime == object.frameTime &&
			loopCounter == object.loopCounter &&
			loop == object.loop
			)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Sprite::operator <(const Sprite &object) const
{
	if (lastFrame < object.lastFrame)
			return true;
		else
			return false;
}

bool Sprite::operator >(const Sprite &object) const
{
	if (lastFrame > object.lastFrame)
		return true;
	else
		return false;
}

bool Sprite::operator*( Sprite &object)
{
	/*
	if (hitBox->operator*(*object.hitBox))
	{
		if (hitBox->box.x < object.hitBox->box.x)
		{
			hitBox->right = object.textureID;
			object.hitBox->left = textureID;


		}

		if (hitBox->box.x > object.hitBox->box.x)
		{
			hitBox->left = object.textureID;
			object.hitBox->right = textureID;

		}

		if (hitBox->box.y < object.hitBox->box.y)
		{
			hitBox->up = object.textureID;
			object.hitBox->down = textureID;


		}

		if (hitBox->box.y > object.hitBox->box.y)
		{
			hitBox->down = object.textureID;
			object.hitBox->up = textureID;

		}

		return true;
	}
	else
		return false;

		*/

	return false;
}

void Sprite::update()
{
	if (lastFrame > firstFrame)
	{
		if (animationState == AnimationStates::FORWARD)
		{
			if (frameCounter < frameTime)
			{
				frameCounter++;
			}
			else
			{
				if (actualFrame < lastFrame)
				{
					actualFrame++;
				}
				frameCounter = 0;
			}
		}

		if (animationState == AnimationStates::BACKWARD)
		{
			if (frameCounter < frameTime)
			{
				frameCounter++;
			}
			else
			{
				if (actualFrame > firstFrame)
				{
					actualFrame--;
				}
				frameCounter = 0;
			}
		}

		if (animationState == AnimationStates::LOOP_FORWARD)
		{
			if (frameCounter < frameTime)
			{
				frameCounter++;
			}
			else
			{
				if (actualFrame < lastFrame)
				{
					actualFrame++;
				}
				else
				{
					actualFrame = firstFrame;
					loopCounter++;
				}
				frameCounter = 0;
			}
		}

		if (animationState == AnimationStates::LOOP_BACKWARD)
		{
			if (frameCounter < frameTime)
			{
				frameCounter++;
			}
			else
			{
				if (actualFrame > firstFrame)
				{
					actualFrame--;
				}
				else
				{
					actualFrame = lastFrame;
					loopCounter++;
				}
				frameCounter = 0;
			}
		}

		if (animationState == AnimationStates::PAUSE)
		{

		}

		if (animationState == AnimationStates::STOP)
		{
			frameCounter = 0;
			actualFrame = firstFrame;
		}
	}

}

void Sprite::print() const
{
	cout << "Actual Frame = " << actualFrame << endl;
	cout << "First Frame = " << firstFrame << endl;
	cout << "Last Frame = " << lastFrame << endl;
	cout << "Active = " << active << endl;

	cout << "Texture Unit = " << textureUnit << endl;
	cout << "Texture ID = " << textureID << endl;
	cout << "Texture Offset = [" << textureOffset.x << ", " << textureOffset.y << ", " << textureOffset.z << ", " << textureOffset.w << "]" << endl;
	cout << "Texture Page Offset = [" << texturePageOffset << "]" << endl;
	cout << "Position Offset = [" << positionOffset.x << ", " << positionOffset.y << ", " << textureOffset.z << ", " << textureOffset.w << "]" << endl;

	transformation.print();

	if (hitBox.size() > 0)
	{
		for (uint i = 0; i < hitBox.size() - 1; i++ )
		{
			if (hitBox[i] != NULL)
				hitBox[i]->print();
		}

		cout << "Color [0] = [ " << color[0].r << ", " << color[0].g << ", " << color[0].b << ", " << color[0].a << " ]" << endl;
		cout << "Color [1] = [ " << color[1].r << ", " << color[1].g << ", " << color[1].b << ", " << color[1].a << " ]" << endl;
		cout << "Color [2] = [ " << color[2].r << ", " << color[2].g << ", " << color[2].b << ", " << color[2].a << " ]" << endl;
		cout << "Color [3] = [ " << color[3].r << ", " << color[3].g << ", " << color[3].b << ", " << color[3].a << " ]" << endl;
	}
}
