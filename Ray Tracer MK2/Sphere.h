#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include "Vector.h"
#include "Ray.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:

	Sphere(Vector& center, float radius, Color& color);
	
	float distanceAlongRay(Ray& ray);

	Vector calculateNormal(Vector& point);
};

#endif