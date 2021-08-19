#include "Ray.h"
#include "Vector.h"

Ray::Ray(const Vector& origin,const Vector& direction) {
	this->origin = origin;
	this->direction = direction;
}

Vector Ray::at(float distance) {
	return this->origin + (this->direction.normalized() * distance);
}