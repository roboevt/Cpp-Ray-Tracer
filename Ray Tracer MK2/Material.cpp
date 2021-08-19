#include "Material.h"

Color Material::getColor() {
	return this->color;
}

/*
Collision Material::calculateCollision(Collision& collision) {
	if (collision.remainingBounces > 0) {
		if (this->shader == 1) { // Diffuse
			collision.outVector = collision.point + collision.normal + randomInUnitSphere();
		}
	}
	else { // No bounces left, return the hit objects color
		collision.color = this->color;
	}
	return collision;
}

Vector Material::randomInUnitSphere() {
	Vector test = Vector(1, 1, 1);
	while (test.magnitudeSquared() > 1) {
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		test = Vector(x, y, z);
	}
}*/