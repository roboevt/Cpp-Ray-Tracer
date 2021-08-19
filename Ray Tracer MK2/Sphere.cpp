#include "Sphere.h"

Sphere::Sphere(Vector& center, float radius, Material material) {
	this->center = center;
	this->radius = radius;
	this->material = material;
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

//Vector Sphere::calculateNormal(Vector& point) {
//	return point - this->center;
//}