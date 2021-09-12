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
	void operator+=(const Vector& other);
	Vector operator-(const Vector& other);
	void operator-=(const Vector& other);
	Vector operator*(const float scale);   // multiple vector by scalar
	float operator*(const Vector& other);  // dot product

	float dot(const Vector& other);

	float magnitudeSquared();

	float magnitude();

	Vector normalized();

	float getX(); // This one is fine
	float getY(); // These might not be optimal in SIMD
	float getZ(); // But shouldn't be called too much anyway

	void setX(float x);  // These are also also a bit slow in SIMD
	void setY(float y);  // And also shouldn't be neccesary too often
	void setZ(float z);

	static bool usingSimd();

	Vector() = default;
};

#endif