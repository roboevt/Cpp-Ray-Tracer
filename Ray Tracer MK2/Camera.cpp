#include "Camera.h"

Camera::Camera() {
	this->location = Vector(0, 0, 0);
	this->xAngle = 0;
	this->yAngle = 90;
	this->zAngle = 0;
	this->zoom = 2;
	this->speed = .002f;
}

Ray Camera::generateRay(float x, float y) const {
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

float Camera::toRadians(float degrees) const {
	return degrees * M_PI / 180.0f;
}

void Camera::moveCamera(long long timestep) {
	float distance = this->speed * timestep;
	
	if (GetKeyState('W') & 0x8000) {
		this->location.setZ(this->location.getZ() + (speed * this->location.getY() / 2) * sin(this->toRadians(yAngle)) * distance);
		this->location.setX(this->location.getX() + (speed * this->location.getY() / 2) * cos(this->toRadians(yAngle)) * distance);
	}

	if (GetKeyState('A') & 0x8000) {
		this->location.setZ(this->location.getZ() - (speed * this->location.getY() / 2) * cos(this->toRadians(yAngle)) * distance);
		this->location.setX(this->location.getX() + (speed * this->location.getY() / 2) * sin(this->toRadians(yAngle)) * distance);
	}
	if (GetKeyState('S') & 0x8000) {
		this->location.setZ(this->location.getZ() - (speed * this->location.getY() / 2) * sin(this->toRadians(yAngle)) * distance);
		this->location.setX(this->location.getX() - (speed * this->location.getY() / 2) * cos(this->toRadians(yAngle)) * distance);
	}
	if (GetKeyState('D') & 0x8000) {
		this->location.setZ(this->location.getZ() + (speed * this->location.getY() / 2) * cos(this->toRadians(yAngle)) * distance);
		this->location.setX(this->location.getX() - (speed * this->location.getY() / 2) * sin(this->toRadians(yAngle)) * distance);
	}
	if (GetKeyState(VK_LSHIFT) & 0x8000) {
		this->location.setY(this->location.getY() + distance * .0001f);
	}
	if (GetKeyState(VK_LCONTROL) & 0x8000) {
		this->location.setY(this->location.getY() - distance * .0001f);
	}

	if (GetKeyState('R') & 0x8000) {
		this->zoom += this->zoom * distance/1000;
	}
	if (GetKeyState('F') & 0x8000) {
		this->zoom -= this->zoom * distance/1000;
	}
	if (GetKeyState(VK_LEFT) & 0x8000) {
		this->yAngle -= .02f * distance;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000) {
		this->yAngle += .02f * distance;
	}
	if (GetKeyState(VK_UP) & 0x8000) {
		this->xAngle -= .02f * distance;
	}
	if (GetKeyState(VK_DOWN) & 0x8000){
		this->xAngle += .02f * distance;
	}
}