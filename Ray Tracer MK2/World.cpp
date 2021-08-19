#include "World.h"
#include <vector>

World::World(vector <Sphere> spheres) {
	this->spheres = spheres;
}

float World::distanceAlongRay(Ray& ray) {
	float minDistance = FLT_MAX;
	float testDistance;

	for (Sphere sphere : this->spheres) {
		testDistance = sphere.distanceAlongRay(ray);
		if (testDistance != 0 && testDistance < minDistance) {
			minDistance = testDistance;
		}
	}
	if (minDistance == FLT_MAX) {
		return 0;
	}
	else {
		return minDistance;
	}
}