#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
#include <immintrin.h>
#include <stdio.h>

using namespace std;

class Vector
{
public:
	//float x;
	//float y;
	//float z;
	__m128 sseVector;

	Vector(float x, float y, float z);
	Vector(__m128);
	Vector() = default;

	//friend ostream& operator<<(ostream& strm, const Vector& vector) {
	//	return strm << vector.x << ", " << vector.y << ", " << vector.z;
	//}

	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	Vector operator*(const float scale);

	float dot(const Vector& other);

	float magnitudeSquared();

	float magnitude();

	Vector normalized();

	float getX();
	float getY();
	float getZ();

	void setX(float x);  // Might not be optimal
	void setY(float y);  // But shouldn't be called too much anyway
	void setZ(float z);
};

#endif