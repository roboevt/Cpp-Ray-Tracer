#pragma once
#include <vector>
#include "Sphere.h"
class World
{
public:
	vector <Sphere> spheres;

	World(vector <Sphere> spheres);

	float distanceAlongRay(Ray& ray);
};

