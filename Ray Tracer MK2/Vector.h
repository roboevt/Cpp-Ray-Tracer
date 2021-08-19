#pragma once

#include <math.h>
#include <iostream>

using namespace std;

class Vector
{
public:
	float x;
	float y;
	float z;

	Vector(float x, float y, float z);
	Vector() = default;

	friend ostream& operator<<(ostream& strm, const Vector& vector) {
		return strm << vector.x << ", " << vector.y << ", " << vector.z;
	}

	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	Vector operator*(const float scale);

	float dot(const Vector& other);

	float magnitudeSquared();

	float magnitude();

	Vector normalized();
};

