
#include "stdafx.h"

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Transformation
{
public:
	vec3	translate;
	vec3	rotate;
	vec3	scale;
	vec3	pivot;

    Transformation();
    ~Transformation();

    void print() const;
};
#endif


