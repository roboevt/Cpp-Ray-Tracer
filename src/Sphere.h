#ifndef SPHERE_H
#define SPHERE_H
#include "Ray.h"
#include "Hittable.h"

#include "Vector.h"


class Sphere : public Hittable
{
public:

	Sphere(Vector& center, float radius, Material& material);
	
	float distanceAlongRay(Ray& ray) const;

	Vector calculateNormal(Vector& point) const;
};

#endif // !SPHERE_H