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
		Ray nextRay = Ray(collision.point, collision.outVector);
		return calcColor(nextRay, remainingBounces - 1) * 0.5;
	}
	return Color(255, 255, 255);  // did not hit anything, so return background color
}

bool World::hit(Ray ray, Collision& collision) {
	float closest = std::numeric_limits<float>::max();
	bool hitAnything = false;
	for (Sphere sphere : this->spheres) {
		float distance = sphere.distanceAlongRay(ray);
		if (distance > 0 && distance < closest) {
			hitAnything = true;
			closest = distance;
			collision.hitObject = sphere;
			collision.point = ray.origin + ray.direction.normalized() * distance;
		}
	}
	if (hitAnything) {
		collision.normal = (collision.point - collision.hitObject.center).normalized();  // should probably be normalized
		collision.point = collision.point + collision.normal * .01;
		collision.inVector = collision.outVector;
		collision.outVector = calcBounce(collision);
	}
	return hitAnything;
}

Vector World::calcBounce(Collision& collision) {
	if (collision.hitObject.shader == 1) {  // diffuse
		return (collision.normal + randomInUnitSphere()).normalized();  // might not need to normalize
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