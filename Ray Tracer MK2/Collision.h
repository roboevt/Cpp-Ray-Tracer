#pragma once
#ifndef COLLISION_H
#define COLLISION_H

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
	float absorbtion;
	int remainingBounces;

	Collision();
};

#endif