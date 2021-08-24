#include "World.h"

World::World(vector <Sphere> spheres) {
	this->spheres = spheres;
}

Color World::calcColor(Ray ray, int remainingBounces) {
	if (remainingBounces == 0) { // no bounces left (base case)
		return Color(0, 0, 0);
	}
	Collision collision;
	if (hit(ray, collision)) {
		if (collision.hitObject.shader == 3) {
			return Color(1000,1000,1000);
		}
		Ray nextRay = Ray(collision.point, collision.outVector);
		return calcColor(nextRay, remainingBounces - 1) * collision.absorbtion;
	}
	return this->backgroundColor;
}

bool World::hit(Ray ray, Collision& collision) {
	float closest = std::numeric_limits<float>::max();
	bool hitAnything = false;
	for (Sphere& sphere : this->spheres) {
		float distance = sphere.distanceAlongRay(ray);
		if (distance > 0 && distance < closest) {
			hitAnything = true;
			closest = distance;
			collision.hitObject = sphere;
			collision.point = ray.at(distance);
		}
	}
	if (hitAnything) {
		collision.normal = (collision.point - collision.hitObject.center).normalized();  // should probably be normalized
		collision.inVector = collision.outVector;
		collision.outVector = calcBounce(collision);
	}
	return hitAnything;
}

Vector World::calcBounce(Collision& collision) {
	if (collision.hitObject.shader == 1) {  // diffuse
		collision.absorbtion = collision.hitObject.absorbtion;
		return (collision.normal + randomInUnitSphere()).normalized();
	}
	if (collision.hitObject.shader == 2) {  // reflective
		collision.absorbtion = 1;
		return Vector(0, 0, 0) - ((collision.normal * collision.inVector.dot(collision.normal)) * 2) - collision.inVector;
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