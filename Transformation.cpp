#pragma once
#include "stdafx.h"

Transformation::Transformation()
{
	translate = vec3();
	rotate = vec3();
	scale = vec3();
	pivot = vec3();
}

Transformation::~Transformation()
{
	
}

void Transformation::print() const
{
	cout << "Translate = [" << translate.x << "," << translate.y << "," << translate.z << "]" << endl;
	cout << "Rotate = [" << rotate.x << "," << rotate.y << "," << rotate.z << "]" << endl;
	cout << "Scale = [" << scale.x << "," << scale.y << "," << scale.z << "]" << endl;
	cout << "Pivot = [" << pivot.x << "," << pivot.y << "," << pivot.z << "]" << endl;
}
