#include "Sphere.h"

Sphere::Sphere(Vector& center, float radius, Color& color) {
	this->center = center;
	this->radius = radius;
	this->color = color;
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
	float sqrtd = sqrt(discriminant);
	float root1 = (-halfB - sqrtd) / a;
	float root2 = (-halfB + sqrtd) / a;
	if (root1 < root2) {
		return root1;
	}
	return root2;
	
}

Vector Sphere::calculateNormal(Vector& point) {
	return (point - this->center).normalized();
}