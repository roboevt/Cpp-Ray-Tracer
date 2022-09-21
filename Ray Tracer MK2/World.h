#pragma once
#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Sphere.h"
#include "Collision.h"
#include "Ray.h"
#include <thread>
#include <immintrin.h>

class World
{
public:
	std::vector <Sphere> spheres;
	Color backgroundColor;

	World(std::vector <Sphere> spheres);

	Color calcColor(Ray& ray, int remainingBounces) const;

	bool hit(Ray& ray, Collision& collision) const;

	Vector calcBounce (Collision& collision) const;

	Vector randomInUnitSphere() const;
};

#endif