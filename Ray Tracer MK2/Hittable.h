#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "Vector.h"
#include "Color.h"

class Hittable
{
public:
	Vector center;
	float radius;
	Color color;
	int shader;

	Vector calculateNormal(Vector& point);
};

#endif