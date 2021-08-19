#pragma once
#include "Vector.h"
#include "Material.h"

class Hittable
{
public:
	Vector center;
	float radius;
	Material material;
};

