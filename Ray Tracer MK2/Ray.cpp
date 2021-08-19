#include "Ray.h"
#include "Vector.h"

Ray::Ray(Vector& origin, Vector& direction) {
	this->origin = origin;
	this->direction = direction;
}