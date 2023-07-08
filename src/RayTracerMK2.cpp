#include <GLFW/glfw3.h>
#include <math.h>
#include <stdint.h>

#include <algorithm>
#include <chrono>
#include <execution>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "Camera.h"
#include "Collision.h"
#include "Color.h"
#include "Image.h"
#include "Material.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector.h"
#include "World.h"

constexpr int width = 640;
constexpr int height = 480;
constexpr float zoom = 1500;
const int threadCount = std::thread::hardware_concurrency();

static void renderLine(int offset, const Camera& camera, const World& world, uint8_t pixelArray[width][height][3]) {
    srand(std::hash<std::thread::id>{}(std::this_thread::get_id()));
    Ray cameraRay;
    for (int y = offset; y < height; y += threadCount) {
        for (int x = 0; x < width; ++x) {
            float xCam = (x - width / 2.0f);
            float yCam = (-y + height / 2.0f);
            cameraRay = camera.generateRay(xCam, yCam);
            Color pixelColor = Color(0, 0, 0);
            for (int s = 0; s < camera.getSamples(); ++s) {
                pixelColor = pixelColor + world.calcColor(cameraRay, camera.getBounceLimit() + 1);
                if(pixelColor == world.getBackgroundColor()) {
                    break;  // TODO find a better way to check if no collision occured
                }
            }
            Color finalPixelColor = pixelColor.output();
            pixelArray[x][y][0] = finalPixelColor.r;
            pixelArray[x][y][1] = finalPixelColor.g;
            pixelArray[x][y][2] = finalPixelColor.b;
        }
    }
}

static void drawArray(GLFWwindow* window, uint8_t pixelArray[width][height][3]) {
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

static void checkInput(GLFWwindow* window, Camera& camera) {
    static bool samplesPressed = false;
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS) {
        if (!samplesPressed) {
            camera.samples *= 2;
            samplesPressed = true;
        }
    } else if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS) {
        if (!samplesPressed) {
            camera.samples /= 2;
            samplesPressed = true;
        }
    } else {
        samplesPressed = false;
    }

    static bool plusOrMinusPressed = false;
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
        if (!plusOrMinusPressed) {
            ++camera.bounceLimit;
            plusOrMinusPressed = true;
        }
    } else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
        if (!plusOrMinusPressed) {
            plusOrMinusPressed = true;
            if (camera.bounceLimit > +1) {
                camera.bounceLimit--;
            }
        }
    } else {
        plusOrMinusPressed = false;
    }
}

static World generateWorld() {
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

    std::vector<Sphere> spheres;
    spheres.push_back(sphere1);
    spheres.push_back(sphere2);
    spheres.push_back(sphere3);
    spheres.push_back(sphere4);
    World world = World(spheres);
    world.backgroundColor = Color(220, 240, 255);
    return world;
}

int main() {
    World world = generateWorld();

    Camera camera = Camera();
    camera.zoom = zoom;
    camera.location = Vector(0, .1, -1);
    camera.samples = 5;
    camera.bounceLimit = 3;

    Vector origin = Vector(0, 0, 0);
    Vector direction = Vector(0, 0, 0);
    Ray cameraRay = Ray(origin, direction);
    Collision collision;
    auto pixelArray = new uint8_t[width][height][3];

    long long renderTime = 0;
    long long drawTime = 0;
    long long overallTime = 0;
    long long frameTime = 0;

    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(width, height, "Ray Tracer", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    while (!glfwWindowShouldClose(window)) {
        auto frameBegin = std::chrono::high_resolution_clock::now();

        camera.moveCamera(window, frameTime);
        checkInput(window, camera);

        std::vector<std::jthread> threads(threadCount);

        for (int i = 0; i < threadCount; ++i) {
            threads[i] = std::jthread(renderLine, i, std::ref(camera), std::ref(world), pixelArray);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        for (auto& thread : threads) {
            thread.join();
        }

        auto renderEnd = std::chrono::high_resolution_clock::now();

        drawArray(window, pixelArray);  // Takes 5 ms because of vsync/gsync.

        auto frameEnd = std::chrono::high_resolution_clock::now();

        frameTime = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameBegin).count();
        renderTime = std::chrono::duration_cast<std::chrono::microseconds>(renderEnd - frameBegin).count();
        drawTime = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - renderEnd).count();
        std::cout << "Frame time: " << frameTime / 1000 << "ms\t"
                  << "Render time: " << renderTime / 1000 << "ms\t"
                  << "Draw time: " << drawTime / 1000 << "ms\t"
                  << "Total time: " << (frameTime + overallTime) / 1000 << "ms\n";
        std::cout << "Samples: " << camera.samples << "\tBounce Limit: " << camera.bounceLimit << '\n';
    }

    glfwTerminate();
    delete[] pixelArray;
    return 0;
}