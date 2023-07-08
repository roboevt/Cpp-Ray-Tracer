#include <iostream>
//#include <Windows.h>
#include <GLFW/glfw3.h>
//#include <gdiplus.h>
#include <math.h>
#include <vector>
#include <thread>
#include <stdint.h>
#include <chrono>
#include <mutex>
#include <future>
#include <algorithm>
#include <execution>

#include "Ray.h"
#include "Sphere.h"
#include "World.h"
#include "Collision.h"
#include "Color.h"
#include "Camera.h"
#include "Vector.h"
#include "Material.h"
#include "Image.h"

//using namespace std;

GLFWwindow* window;

const int width = 1280;
const int height = 720;
int frames = 1000000;
int samples = 5;
int bounceLimit = 3;
float zoom = 1500;
const int threadCount = 12;
bool plusOrMinusPressed = false;
bool samplesPressed = false;


void renderLine(int offset, const Camera* camera, const World* world, uint8_t pixelArray[width][height][3]) {
	srand(std::hash<std::thread::id>{}(std::this_thread::get_id()));  // Seperate threads need distinct random number generation
	int y;
	Ray cameraRay;
	for (int i = offset; i < height; i += threadCount) {
		y = i;
		for (int x = 0; x < width; ++x) {
			float xCam = (x - width / 2.0f);
			float yCam = (-y + height / 2.0f);
			cameraRay = camera->generateRay(xCam, yCam);
			Color pixelColor = Color(0, 0, 0);

			for (int s = 0; s < samples; ++s) {
				pixelColor = pixelColor + world->calcColor(cameraRay, bounceLimit + 1);
				if (pixelColor.r == world->backgroundColor.r && pixelColor.g == world->backgroundColor.g && pixelColor.b == world->backgroundColor.b) {
					break;  // There is a better way to pass this information back. But it does save a ton of time not resampling the background
				}
			}
			Color finalPixelColor = pixelColor.output();
			pixelArray[x][y][0] = finalPixelColor.r;
			pixelArray[x][y][1] = finalPixelColor.g;
			pixelArray[x][y][2] = finalPixelColor.b;
		}
	}
}

void drawArray(uint8_t pixelArray[width][height][3]) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			glColor3ub(pixelArray[x][y][0], pixelArray[x][y][1], pixelArray[x][y][2]);
			float xOut = (static_cast<float>(x) / static_cast<float>(width)) * 2 - 1;
			float yOut = (static_cast<float>(y) / static_cast<float>(height)) * 2 - 1;
			glVertex2f(xOut, -yOut);
		}
	}
	glEnd();
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void checkInput() {
	// if (GetKeyState(VK_PRIOR) & 0x8000) {
	// 	if (!samplesPressed) {
	// 		samplesPressed = true;
	// 		samples = samples * 2;
	// 	}
	// } else if (GetKeyState(VK_NEXT) & 0x8000) {
	// 	if (!samplesPressed) {
	// 		samplesPressed = true;
	// 		if (samples > 1) {
	// 			samples = samples / 2;
	// 		}
	// 	}
	// }
	// else {
	// 	samplesPressed = false;
	// }

	// if (GetKeyState(VK_OEM_PLUS) & 0x8000) {
	// 	if (!plusOrMinusPressed) {
	// 		++bounceLimit;
	// 		plusOrMinusPressed = true;
	// 	}
	// } else if (GetKeyState(VK_OEM_MINUS) & 0x8000) {
	// 	if (!plusOrMinusPressed) {
	// 		plusOrMinusPressed = true;
	// 		if (bounceLimit >+ 1) {
	// 			bounceLimit--;
	// 		}
	// 	}
	// }
	// else {
	// 	plusOrMinusPressed = false;
	// }
}

World generateWorld() {
	Vector sphere1Location = Vector(0, .1f, 0);
	Material sphere1Material = Material();
	Sphere sphere1 = Sphere(sphere1Location, .1f, sphere1Material);
	sphere1.material.shader = reflective;
	sphere1.material.absorbtion = .3;

	Vector sphere2Location = Vector(0, -100, 0);
	Material sphere2Material = Material();
	sphere2Material.color = Color(255, 255, 0);
	Sphere sphere2 = Sphere(sphere2Location, 100, sphere2Material);
	sphere2.material.shader = diffuse;
	sphere2.material.absorbtion = .9f;

	Vector sphere3Location = Vector(.14f, .1f, 0);
	Material sphere3Material = Material();
	sphere3Material.color = Color(0, 255, 255);
	Sphere sphere3 = Sphere(sphere3Location, .05f, sphere3Material);
	sphere3.material.shader = diffuse;
	sphere3.material.absorbtion = .8f;

	Vector sphere4Location = Vector(-.14f, .1f, 0);
	Material sphere4Material = Material();
	sphere4Material.color = Color(255, 0, 0);
	Sphere sphere4 = Sphere(sphere4Location, .05f, sphere4Material);
	sphere4.material.shader = diffuse;
	sphere4.material.absorbtion = .8f;

	std::vector <Sphere> spheres;
	spheres.push_back(sphere1);
	spheres.push_back(sphere2);
	spheres.push_back(sphere3);
	spheres.push_back(sphere4);
	World world = World(spheres);
	world.backgroundColor = Color(220, 240, 255);
	return world;
}

int main()
{
	World world = generateWorld();

	Camera camera = Camera();
	camera.zoom = zoom;
	camera.location = Vector(0, .1, -1);

	Vector origin = Vector(0, 0, 0);
	Vector direction = Vector(0, 0, 0);
	Ray cameraRay = Ray(origin, direction);
	Collision collision;
	auto pixelArray = new uint8_t[width][height][3];

	std::vector<std::future<void>> workers;

	long long renderTime = 0;
	long long drawTime = 0;
	long long overallTime = 0;
	long long totalTime = 0;

	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(width, height, "Ray Tracer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	while (!glfwWindowShouldClose(window))
	{
		std::chrono::steady_clock::time_point overallBegin = std::chrono::steady_clock::now();
		for (int f = 0; f < frames; f++) {
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

			camera.moveCamera(totalTime);
			checkInput();
			/*for (int w = 0; w < threadCount; w++) {
				workers.push_back(std::async(std::launch::async, renderLine, w, &camera, &world, pixelArray));
			}
			for (int w = 0; w < threadCount; w++) {
				workers[w].wait();
			}
			for (int i = 0; i < threadCount; i++) {
				renderLine(i, &camera, &world, pixelArray);
			}*/
			std::vector<int> offsets;
			for (int i = 0; i < threadCount; i++) {
				offsets.push_back(i);
			}

			std::for_each(std::execution::par_unseq, std::begin(offsets), std::end(offsets), [camera, world, pixelArray](int i) {
				renderLine(i, &camera, &world, pixelArray);
			});

			drawArray(pixelArray);  // Takes 5 ms because of vsync/gsync.
			std::chrono::steady_clock::time_point totalEnd = std::chrono::steady_clock::now();

			totalTime = std::chrono::duration_cast<std::chrono::microseconds>(totalEnd - begin).count();
			std::cout << "Frame time: " << totalTime / 1000 << "ms\t" << "Samples: " << samples << "\tBounce Limit: " << bounceLimit << '\n';
		}
		std::chrono::steady_clock::time_point overallEnd = std::chrono::steady_clock::now();
		overallTime = std::chrono::duration_cast<std::chrono::microseconds>(overallEnd - overallBegin).count();
		std::cout << "Total time: " << overallTime / 1000 << "ms\tAverage frame time: " << overallTime / 1000 / frames << "ms";
		delete[] pixelArray;

		glfwTerminate();
		return 0;
	}
	int x = 10;
	int* px = &x;
}