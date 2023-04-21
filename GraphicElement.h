#pragma once
#include "stdafx.h"

#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

class GraphicElement
{
	public:
	Transformation transformation;
	vec4 color;
	vec4 alphaColor;

	__declspec(dllexport) GraphicElement() {};
	__declspec(dllexport) ~GraphicElement(){};


	__declspec(dllexport) virtual void update() = 0;
	__declspec(dllexport) virtual void print() const = 0;
};

#endif // !GRAPHICELEMENT_H

