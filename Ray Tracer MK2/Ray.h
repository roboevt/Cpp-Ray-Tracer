#pragma once
#include "Vector.h"

class Ray
{
public:
	Vector origin;
	Vector direction;

	Ray(Vector& origin,Vector& direction);
};

