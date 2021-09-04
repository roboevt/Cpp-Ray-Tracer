#pragma once
#ifndef SPHERE_H
#define SPHERE_H
#include "Ray.h"
#include "Hittable.h"

#include "Vector.h"


class Sphere : public Hittable
{
public:

	Sphere(Vector& center, float radius, Color& color);
	
	float distanceAlongRay(Ray& ray);

	Vector calculateNormal(Vector& point);
};

#endif