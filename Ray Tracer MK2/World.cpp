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
			collision.color = collision.color + collision.hitObject.color;
			collision.normal = collision.hitObject.calculateNormal(collision.point);
			collision = evaluateCollision(collision);
			return this->calcNextCollision(collision);
		}
		else { // hit nothing, return background color
			collision.remainingBounces = 0;
			collision.color = collision.color + Color(68, 85, 90);  // light blue
			return collision;
		}
	}
	else { //No bounces left
		return collision;
	}
}

Collision World::evaluateCollision(Collision& collision) {
	if (collision.hitObject.shader == 1) {  // diffuse
		if (collision.remainingBounces > 0) {
			collision.outVector = collision.point + collision.normal + randomInUnitSphere();
		}
		else {
			cout << collision.color.samples;
			collision.color = collision.color + collision.hitObject.color;
		}
	}
	return collision;
}

Vector World::randomInUnitSphere() {
	Vector test = Vector(1, 1, 1);
	while (test.magnitudeSquared() > 1) {
		test.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		test.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		test.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
	return test;
}