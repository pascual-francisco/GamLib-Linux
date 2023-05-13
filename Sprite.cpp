#include "stdafx.h"

Sprite::Sprite(GLuint palette, GLuint page):GraphicElement()
{
	init(palette, page);
}

Sprite::~Sprite()
{
	if(ptrAnimation != nullptr)
		delete ptrAnimation;
}

void Sprite::init(GLuint palette, GLuint page)
{
	texturePalette = palette;
	palettePage = page;
	positionOffset = vec2(0.0f, 0.0f);
   ptrAnimation = nullptr;
}


Sprite::Sprite(const Sprite &object)
{
	if (&object != this)
	{
		positionOffset = object.positionOffset;
		ptrAnimation = object.ptrAnimation;

		active = object.active;
		texturePalette = object.texturePalette;
		palettePage = object.palettePage;
		tileSeparation = object.tileSeparation;
		tileCell.x = object.tileCell.x;
		tileCell.y = object.tileCell.y;
		tileDimension.x = object.tileDimension.x;
		tileDimension.y = object.tileDimension.y;
      transformation = object.transformation;
		vertexColor[0] = object.vertexColor[0];
		vertexColor[1] = object.vertexColor[1];
		vertexColor[2] = object.vertexColor[2];
		vertexColor[3] = object.vertexColor[3];
		collisionData = object.collisionData;
	}
}


const Sprite &Sprite::operator=(const Sprite &object)
{
	if (&object != this)
	{
		positionOffset = object.positionOffset;
		ptrAnimation = object.ptrAnimation;
		active = object.active;
		texturePalette = object.texturePalette;
		palettePage = object.palettePage;
		tileSeparation = object.tileSeparation;
		tileCell.x = object.tileCell.x;
		tileCell.y = object.tileCell.y;
		tileDimension.x = object.tileDimension.x;
		tileDimension.y = object.tileDimension.y;
      transformation = object.transformation;
		vertexColor[0] = object.vertexColor[0];
		vertexColor[1] = object.vertexColor[1];
		vertexColor[2] = object.vertexColor[2];
		vertexColor[3] = object.vertexColor[3];
		collisionData = object.collisionData;
	}
	return *this;
}

bool Sprite::operator ==(const Sprite &object) const
{
	if (&object != this)
	{
		if (
		positionOffset == object.positionOffset &&
		ptrAnimation == object.ptrAnimation &&

		active == object.active &&
		texturePalette == object.texturePalette &&
		palettePage == object.palettePage &&
		tileSeparation == object.tileSeparation &&
		tileCell.x == object.tileCell.x &&
		tileCell.y == object.tileCell.y &&
		tileDimension.x == object.tileDimension.x &&
		tileDimension.y == object.tileDimension.y &&
      vertexColor[0] == object.vertexColor[0] &&
		vertexColor[1] == object.vertexColor[1] &&
		vertexColor[2] == object.vertexColor[2] &&
		vertexColor[3] == object.vertexColor[3] &&
		collisionData == object.collisionData
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
	if (tileDimension.x * tileDimension.y < object.tileDimension.x * object.tileDimension.y)
			return true;
		else
			return false;
}

bool Sprite::operator >(const Sprite &object) const
{
	if (tileDimension.x * tileDimension.y > object.tileDimension.x * object.tileDimension.y)
		return true;
	else
		return false;
}

bool Sprite::operator*( Sprite &object)
{
	SDL_Rect a, b;
	a.x = tileCell.x;
	a.y = tileCell.y;
	a.w = tileDimension.x;
	a.h = tileDimension.x;
	b.x = object.tileCell.x;
	b.y = object.tileCell.y;
	b.w = object.tileDimension.x;
	b.h = object.tileDimension.x;

	if(SDL_HasIntersection(&a, &b))
	{
		return true;

	}
	else
	{
		return false;
	}
}

void Sprite::update()
{
	if(ptrAnimation != nullptr)
	{
		ptrAnimation->update();
	}
}

void Sprite::print() const
{
	cout << "******************************************************************************************************************************************************************************" << endl;
	cout << "Sprite Info: " << endl;

	GraphicElement::print();

	if(ptrAnimation != nullptr)
	{
		ptrAnimation->print();
	}
	else
	{
		cout << "Animation is empty"<<endl;
	}
	cout << "Position Offset = [ " << positionOffset.x << " , " << positionOffset.y << " ]" <<endl;
	cout << "Sprite Info: " << endl;
	cout << "******************************************************************************************************************************************************************************" << endl;
}
