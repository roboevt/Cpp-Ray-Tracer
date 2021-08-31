#include "Camera.h"

Camera::Camera() {
	this->location = Vector(0, 0, 0);
	this->xAngle = 0;
	this->yAngle = 90;
	this->zAngle = 0;
	this->zoom = 2;
}

Ray Camera::generateRay(float x, float y) {
	float xRot = x;
	float yRot = y * cos(this->toRadians(xAngle)) - this->zoom * sin(toRadians(this->xAngle));
	float zRot = y * sin(toRadians(this->xAngle)) + this->zoom * cos(toRadians(this->xAngle));

	float xRot1 = xRot * cos(toRadians(this->zAngle)) - yRot * sin(toRadians(this->zAngle));
	float yRot1 = xRot * sin(toRadians(this->zAngle)) + yRot * cos(toRadians(this->zAngle));
	float zRot1 = zRot;

	float xRot2 = zRot1 * cos(toRadians(this->yAngle)) - xRot1 * sin(toRadians(this->yAngle));
	float zRot2 = zRot1 * sin(toRadians(this->yAngle)) + xRot1 * cos(toRadians(this->yAngle));
	float yRot2 = yRot1;
	
	return Ray(this->location, Vector(xRot2, yRot2, zRot2).normalized());
}

float Camera::toRadians(float degrees) {
	return degrees * M_PI / 180;
}