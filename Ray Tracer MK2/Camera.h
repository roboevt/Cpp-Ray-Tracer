#pragma once

#define _USE_MATH_DEFINES

#include "Vector.h"
#include "Ray.h"
#include <cmath>

class Camera
{
public:
	Vector location;
	float xAngle;
	float yAngle;
	float zAngle;
	float zoom;
	Camera();
	Ray generateRay(float x, float y);
	float toRadians(float degrees);
};

