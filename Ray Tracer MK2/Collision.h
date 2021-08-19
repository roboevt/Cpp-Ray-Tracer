#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Hittable.h"
#include "Color.h"

class Collision
{
public:
	Vector point;
	Hittable hitObject;
	Vector inVector;
	Vector outVector;
	Vector normal;
	Color color;
	int remainingBounces;

	Collision();
};