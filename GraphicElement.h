#include "stdafx.h"

#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

class GraphicElement
{
	public:
	bool 			   active;
	GLuint 		   texturePalette;
	GLuint 		   palettePage;
   vec2			   tilePosition;
	vec2			   tileDimension;
   Transformation transformation;
   vec4			   vertexColor[4];
	GLubyte			collisionData;

   GraphicElement()
	{
		active = true;
		texturePalette = 0;
		palettePage = 0;
      tilePosition.x = 0.0;
		tilePosition.y = 0.0;
		tileDimension.x = 16.0f;
		tileDimension.y = 16.0f;
      transformation.pivot.x = 0;
		transformation.pivot.y = 0;
		transformation.pivot.z = 0;
		transformation.translate.x = 0;
		transformation.translate.y = 0;
		transformation.translate.z = 0;
		transformation.scale.x = 1;
		transformation.scale.y = 1;
		transformation.scale.z = 1;
		transformation.rotate.x = 0;
		transformation.rotate.y = 0;
		transformation.rotate.z = 0;
		collisionData = 0;


		for (uint i = 0; i < 4; i++)
		{
			vertexColor[i].r = 0.0f;
			vertexColor[i].g = 0.0f;
			vertexColor[i].b = 0.0f;
		}

		for (uint i = 0; i < 4; i++)
			vertexColor[i].a = 1.0f;
		};

	  ~GraphicElement(){};
	  virtual void update() = 0;
	  virtual void print() const
	{

		cout << "Texture Palette = " << texturePalette << endl;
		cout << "Palette Page  = " << palettePage << endl;
		cout << "Tile Position = [" << tilePosition.x << ", " << tilePosition.y << "]" << endl;
		cout << "Tile Dimension = [" << tileDimension.x << ", " << tileDimension.y << "]" << endl;
      cout << "Collision Data = " << collisionData << endl;
		transformation.print();
		cout << "vertexColor [0] = [ " << vertexColor[0].r << ", " << vertexColor[0].g << ", " << vertexColor[0].b << ", " << vertexColor[0].a << " ]" << endl;
		cout << "vertexColor [1] = [ " << vertexColor[1].r << ", " << vertexColor[1].g << ", " << vertexColor[1].b << ", " << vertexColor[1].a << " ]" << endl;
		cout << "vertexColor [2] = [ " << vertexColor[2].r << ", " << vertexColor[2].g << ", " << vertexColor[2].b << ", " << vertexColor[2].a << " ]" << endl;
		cout << "vertexColor [3] = [ " << vertexColor[3].r << ", " << vertexColor[3].g << ", " << vertexColor[3].b << ", " << vertexColor[3].a << " ]" << endl;

	}
};

#endif // !GRAPHICELEMENT_H


