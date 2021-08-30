#include <iostream>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <gdiplus.h>
#include <math.h>
#include <vector>
#include <thread>
#include <stdint.h>
#include <chrono>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "World.h"
#include "Collision.h"
#include "Color.h"
#include "Camera.h"

using namespace std;

GLFWwindow* window;

const int width = 640;
const int height = 480;
int frames = 1000;
int samples = 25;
int bounceLimit = 3;
float zoom = 15;
const int threadCount = 12;
bool rendering = true;
bool drawing = false;
bool running = true;
bool threadDone[threadCount];

void renderLine(int offset, Camera camera, World& world, unsigned char pixelArray[width][height][3]) {
	srand(std::hash<std::thread::id>{}(std::this_thread::get_id()));  // Seperate threads need distinct random number generation
	while (running) {
		while (!rendering) {};
		for (int i = offset; i < height; i += threadCount) {
			int y = i;
			Ray cameraRay;
			for (int x = 0; x < width; x++) {
				float xCam = (x - width / 2.0f);
				float yCam = (-y + height / 2.0f);
				cameraRay = camera.generateRay(xCam, yCam);
				Color pixelColor = Color(0, 0, 0);

				for (int s = 0; s < samples; s++) {
					pixelColor = pixelColor + world.calcColor(cameraRay, bounceLimit + 1);
					if (pixelColor.r == world.backgroundColor.r && pixelColor.g == world.backgroundColor.g && pixelColor.b == world.backgroundColor.b) {
						break;
					}
				}
				Color finalPixelColor = pixelColor.output();
				pixelArray[x][y][0] = finalPixelColor.r;
				pixelArray[x][y][1] = finalPixelColor.g;
				pixelArray[x][y][2] = finalPixelColor.b;
			}
		}
		threadDone[offset] = true;
		while (!drawing) {};
	}
}

void drawArray(unsigned char pixelArray[width][height][3]) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
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

int main()
{
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(width, height, "Ray Tracer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		Vector sphere1Location = Vector(0, 0, 0);
		Color sphere1Color = Color(255, 255, 255);
		Sphere sphere1 = Sphere(sphere1Location, .1, sphere1Color);
		sphere1.shader = 1;
		sphere1.absorbtion = .3;
		Vector sphere2Location = Vector(0, -10, 0);
		Color sphere2Color = Color(255, 255, 255);
		Sphere sphere2 = Sphere(sphere2Location, 9.9, sphere2Color);
		sphere2.shader = 1;
		sphere2.absorbtion = .9;
		Vector sphere3Location = Vector(.14, 0, 0);
		Color sphere3Color = Color(255, 255, 255);
		Sphere sphere3 = Sphere(sphere3Location, .05, sphere3Color);
		sphere3.shader = 1;
		sphere3.absorbtion = .8;
		Vector sphere4Location = Vector(-.14, 0, 0);
		Color sphere4Color = Color(255, 255, 255);
		Sphere sphere4 = Sphere(sphere4Location, .05, sphere4Color);
		sphere4.shader = 3;
		sphere4.absorbtion = .8;
		vector <Sphere> spheres;
		spheres.push_back(sphere1);
		spheres.push_back(sphere2);
		spheres.push_back(sphere3);
		spheres.push_back(sphere4);
		World world = World(spheres);
		world.backgroundColor = Color(220, 240, 255);

		Camera camera = Camera();
		camera.zoom = zoom * 100;
		camera.location = Vector(0, 0, -1);

		Vector origin = Vector(0, 0, 0);
		Vector direction = Vector(0, 0, 0);
		Ray cameraRay = Ray(origin, direction);
		Collision collision;

		auto pixelArray = new uint8_t [width][height][3];

		vector <thread> workers;

		for (int w = 0; w < threadCount; w++) {
			workers.push_back(thread(renderLine, w, camera, ref(world), pixelArray));
		}
		for (int f = 0; f < frames; f++) {
			chrono::steady_clock::time_point begin = chrono::steady_clock::now();
			//cout << f << endl;

			drawing = false;
			rendering = true;
			for (int w = 0; w < threadCount; w++) {
				while (!threadDone[w]) {};
				threadDone[w] = false;
			}
			rendering = false;
			drawing = true;
			chrono::steady_clock::time_point renderEnd = chrono::steady_clock::now();
			drawArray(pixelArray);
			chrono::steady_clock::time_point totalEnd = chrono::steady_clock::now();
			auto renderTime = chrono::duration_cast<chrono::microseconds>(renderEnd - begin).count();
			auto totalTime = chrono::duration_cast<chrono::microseconds>(totalEnd - begin).count();
			cout << "Render time: " << renderTime / 1000 << "ms\tFrame time: " << totalTime / 1000 << "ms" << endl;
		}
		running = false;
		for (int w = 0; w < threadCount; w++) {
			workers[w].join();
		}
		delete[] pixelArray;

		glfwTerminate();
		return 0;
	}
}