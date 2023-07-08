#ifndef HITTABLE_H
#define HITTABLE_H

#include "Color.h"
#include "Vector.h"
#include "Material.h"

class Hittable
{
public:
	Vector center;
	float radius;
	Material material;

	virtual Vector calculateNormal(Vector& point);
};

#endif // !HITTABLE_H