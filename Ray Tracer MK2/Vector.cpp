#include "Vector.h"
using namespace std;

#define FIRST_MASK 0x71
#define ALL_MASK 0x77

Vector::Vector(float x, float y, float z) {
	//this->x = x;
	//this->y = y;
	//this->z = z;
	this->sseVector = _mm_setr_ps(x, y, z, 0.0f);
}

Vector::Vector(__m128 inputVector) {
	this->sseVector = inputVector;
	
}

float Vector::dot(const Vector& other) {
	//return this->x * other.x + this->y * other.y + this->z * other.z;
	//return fma(this->x, other.x, fma(this->y, other.y, (this->z * other.z)));

	return _mm_cvtss_f32(_mm_dp_ps(this->sseVector, other.sseVector, FIRST_MASK));
}

float Vector::magnitudeSquared() {
	//return this->x * this->x + this->y * this->y + this->z * this->z;

	return _mm_cvtss_f32(_mm_dp_ps(this->sseVector, this->sseVector, FIRST_MASK));
}

float Vector::magnitude() {
	//return sqrt(this->magnitudeSquared());  // Seems to be slower

	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->sseVector, this->sseVector, FIRST_MASK)));
}

Vector Vector::normalized() {
	//float magnitude = this->magnitude();
	//return Vector(this->x / magnitude, this->y / magnitude, this->z / magnitude);

	__m128 inverseSqrt = _mm_rsqrt_ps(_mm_dp_ps(this->sseVector, this->sseVector, ALL_MASK));
	return Vector(_mm_mul_ps(this->sseVector, inverseSqrt));
}

Vector Vector::operator+(const Vector& other) {
	//return Vector(this->x + other.x, this->y + other.y, this->z + other.z);

	return Vector(_mm_add_ps(this->sseVector, other.sseVector));
}

Vector Vector::operator-(const Vector& other) {
	//return Vector(this->x - other.x, this->y - other.y, this->z - other.z);

	return Vector(_mm_sub_ps(this->sseVector, other.sseVector));
}

Vector Vector::operator*(const float scale) {
	//return Vector(this->x * scale, this->y * scale, this->z * scale);

	return Vector(_mm_mul_ps(this->sseVector, _mm_set1_ps(scale)));
}

float Vector::getX() {
	return _mm_cvtss_f32(this->sseVector);
}

float Vector::getY() {
	float result;
	_MM_EXTRACT_FLOAT(result, this->sseVector, 1);
	return result;
}

float Vector::getZ() {
	float result;
	_MM_EXTRACT_FLOAT(result, this->sseVector, 2);
	return result;
}

void Vector::setX(float x) {
	float y = this->getY();
	float z = this->getZ();
	this->sseVector = _mm_setr_ps(x, y, z, 0.0f);
}

void Vector::setY(float y) {
	float x = this->getX();
	float z = this->getZ();
	this->sseVector = _mm_setr_ps(x, y, z, 0.0f);
}

void Vector::setZ(float z) {
	float x = this->getX();
	float y = this->getY();
	this->sseVector = _mm_setr_ps(x, y, z, 0.0f);
}