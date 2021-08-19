#pragma once
#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Sphere.h"
#include "Collision.h"
#include "Ray.h"
class World
{
public:
	vector <Sphere> spheres;

	World(vector <Sphere> spheres);

	Collision calcNextCollision(Collision& collision);
};

#endif