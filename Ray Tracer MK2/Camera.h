#pragma once

#define _USE_MATH_DEFINES

#include "Ray.h"
#include <cmath>
#include <Windows.h>

#include "Vector.h"

class Camera
{
public:
	Vector location;
	float xAngle;
	float yAngle;
	float zAngle;
	float zoom;
	float speed;
	Camera();
	Ray generateRay(float x, float y);
	float toRadians(float degrees);
	void moveCamera(long long timestep);
};

