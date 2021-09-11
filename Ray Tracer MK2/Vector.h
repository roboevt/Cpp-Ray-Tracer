#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <iostream>
#include <immintrin.h>
#include <stdio.h>

#define USE_SIMD

using namespace std;

class Vector
{
public:
#ifdef USE_SIMD:
	__m128 sseVector;
#else
	float x, y, z;
#endif

	Vector(float x, float y, float z);
	Vector(__m128);

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

	static bool usingSimd();

	Vector() = default;
};

#endif