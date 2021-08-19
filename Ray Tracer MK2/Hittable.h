#pragma once
#ifndef HITTABLE_H
#define HITTABLE_H

#include "Vector.h"
#include "Material.h"

class Hittable
{
public:
	Vector center;
	float radius;
	Material material;

	//Vector calculateNormal(Vector& point);
};

#endif