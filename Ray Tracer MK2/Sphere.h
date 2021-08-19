#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Vector center;
	float radius;

	Sphere(Vector& center, float radius);
	
	float distanceAlongRay(Ray& ray);
};

