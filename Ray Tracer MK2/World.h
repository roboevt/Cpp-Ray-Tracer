#pragma once
#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Sphere.h"
#include "Collision.h"
#include "Ray.h"
#include <thread>
class World
{
public:
	vector <Sphere> spheres;
	Color backgroundColor;

	World(vector <Sphere> spheres);

	Color calcColor(Ray ray, int remainingBounces);

	bool hit(Ray ray, Collision& collision);

	Vector calcBounce (Collision& collision);

	Vector randomInUnitSphere();
};

#endif