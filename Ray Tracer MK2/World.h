#pragma once
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

