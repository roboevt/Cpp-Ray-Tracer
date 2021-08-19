#pragma once
#ifndef RAY_H
#define RAY_H

#include "Vector.h"

class Ray
{
public:
	Vector origin;
	Vector direction;

	Ray(const Vector& origin,const Vector& direction);

	Vector at(float distance);
};

#endif