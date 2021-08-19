#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
public:

	Sphere(Vector& center, float radius, Material material);
	
	float distanceAlongRay(Ray& ray);
};

