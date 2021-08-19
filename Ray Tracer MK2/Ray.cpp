#include "Ray.h"
#include "Vector.h"

Ray::Ray(const Vector& origin,const Vector& direction) {
	this->origin = origin;
	this->direction = direction;
}