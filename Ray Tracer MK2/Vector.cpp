#include "Vector.h"
#include <math.h>
#include <iostream>
using namespace std;


Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Vector::dot(const Vector& other) {
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

float Vector::magnitudeSquared() {
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vector::magnitude() {
	return sqrt(this->magnitudeSquared());
}

Vector Vector::normalized() {
	float magnitude = this->magnitude();
	return Vector(this->x / magnitude, this->y / magnitude, this->z / magnitude);
}

Vector Vector::operator+(const Vector& other) {
	return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector Vector::operator-(const Vector& other) {
	return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector Vector::operator*(const float scale) {
	return Vector(this->x * scale, this->y * scale, this->z * scale);
}