#pragma once
#include "Vector.h"
#include "Ray.h"

class Sphere
{
public:
	Vector center;
	float radius;

	Sphere(Vector& center, float radius);
	
	float distanceAlongRay(Ray& ray);
};

