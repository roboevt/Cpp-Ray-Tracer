#ifndef CAMERA_H
#define CAMERA_H

#define _USE_MATH_DEFINES

#include "Ray.h"
#include <GLFW/glfw3.h>

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
	int samples;
	int bounceLimit;

	int getSamples() const {
		return this->samples;
	}
	int getBounceLimit() const {
		return this->bounceLimit;
	}
	Camera();
	Ray generateRay(float x, float y) const;
	float toRadians(float degrees) const;
	void moveCamera(GLFWwindow* window, long long timestep);
};

#endif // !CAMERA_H