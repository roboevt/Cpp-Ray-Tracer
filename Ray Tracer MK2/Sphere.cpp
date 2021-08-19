#include "Sphere.h"
#include "Vector.h"

Sphere::Sphere(Vector& center, float radius) {
	this->center = center;
	this->radius = radius;
}

float Sphere::distanceAlongRay(Ray& ray) {
	Vector oc = ray.origin - this->center;
	float a = ray.direction.magnitudeSquared();
	float halfB = oc.dot(ray.direction);
	float c = oc.magnitudeSquared() - this->radius * this->radius;
	float discriminant = halfB * halfB - a * c;
	if (discriminant < 0) {
		return 0;
	}
	else {
		return (-halfB - sqrt(discriminant)) / a;
	}
}