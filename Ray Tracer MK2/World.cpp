#include "World.h"
#include "Collision.h"
#include "Ray.h"
#include <vector>

World::World(vector <Sphere> spheres) {
	this->spheres = spheres;
}

Collision World::calcNextCollision(Collision& collision) {
	if (collision.remainingBounces > 0) {
		float minDistance = FLT_MAX;
		float testDistance;

		Ray ray = Ray(collision.point, collision.outVector);
		bool hitSomething = false;
		for (Sphere sphere : this->spheres) {
			testDistance = sphere.distanceAlongRay(ray);
			if (testDistance != 0 && testDistance < minDistance) {
				hitSomething = true;
				minDistance = testDistance;
				collision.hitObject = sphere;
				collision.point = ray.at(testDistance);
			}
		}
		if (hitSomething) {
			collision.remainingBounces -= 1;
			collision.inVector = collision.outVector;
			collision.color = collision.hitObject.material.color;
			//calculate normal here
			return this->calcNextCollision(collision);
		}
		else { // hit nothing, return background color
			//cout << "no hit";
			collision.remainingBounces = 0;
			collision.color = Color(50,50,50);
			return collision;
		}
	}
	else { //No bounces left
		return collision;
	}
}