#include "World.h"
#include "Collision.h"
#include "Ray.h"
#include <vector>

World::World(vector <Sphere> spheres) {
	this->spheres = spheres;
}

Color World::calcColor(Collision collision) {
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
			//collision.normal = (collision.point - collision.hitObject.center).normalized();
			collision.outVector = calcBounce(collision);
			return this->calcColor(collision) * 0.9;
		}
		else { // hit nothing, return background color
			collision.remainingBounces = 0;
			//collision.color = collision.color + Color(68, 85, 90);  // light blue
			//collision.color = collision.color + Color(0, 0, 0);  // black
			//float t = collision.outVector.y;
			//return Color(255, 255, 255) * (1.0-t) + Color(128, 200, 255) * t;
			return Color(255,255,255);  // Background color
		}
	}
	else { //No bounces left
		return Color(0, 0, 0);
		//return collision.hitObject.color;
	}
}

Vector World::calcBounce(Collision& collision) {
	if (collision.hitObject.shader == 1) {  // diffuse
		return (collision.normal + randomInUnitSphere()).normalized();
	}
	return Vector(0, 0, 1);
}

Vector World::randomInUnitSphere() {
	Vector test = Vector(1, 1, 1);
	while (test.magnitudeSquared() > 1.0) {
		test.x = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2.0 - 1.0;
		test.y = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2.0 - 1.0;
		test.z = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2.0 - 1.0;
	}
	return test;
}