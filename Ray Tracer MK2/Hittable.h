#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "Color.h"
#include "Vector.h"

class Hittable
{
public:
	Vector center;
	float radius;
	Color color;
	int shader;
	float absorbtion;

	Vector calculateNormal(Vector& point);
};

#endif