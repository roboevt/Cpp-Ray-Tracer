#include <iostream>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <gdiplus.h>
#include <math.h>
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "World.h"
#include "Collision.h"
#include "Color.h"
#include "Camera.h"

using namespace std;

//HWND consoleWindow = GetConsoleWindow();

int width = 640;
int height = 480;
int frames = 100;
int samples = 10;
int bounceLimit = 3;
float zoom = 15;

int main()
{   
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Ray Tracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

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

        int frame = 0;
        for (int i = 0; i < frames; i++) {
            frame++;
        
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                
                    float xCam = (x - width / 2.0f);
                    float yCam = (-y + height / 2.0f);
                    collision.point = camera.location;
                    cameraRay = camera.generateRay(xCam, yCam);
                    collision.outVector = cameraRay.direction;
                    collision.remainingBounces = bounceLimit;
                    Color pixelColor = Color(0, 0, 0);

                    for (int s = 0; s < samples; s++) {
                        pixelColor = pixelColor + world.calcColor(cameraRay, bounceLimit + 1);
                        if (pixelColor.r == world.backgroundColor.r && pixelColor.g == world.backgroundColor.g && pixelColor.b == world.backgroundColor.b) {
                            break;
                        }
                    }
                    Color finalPixelColor = pixelColor.output();
                    glColor3ub(finalPixelColor.r, finalPixelColor.g, finalPixelColor.b);
                    float xOut = (static_cast<float>(x) / static_cast<float>(width)) * 2 - 1;
                    float yOut = (static_cast<float>(y) / static_cast<float>(height)) * 2 - 1;
                    glVertex2f(xOut, -yOut);
                    //SetPixel(consoleDC, x, y, RGB(pixelColor.output().r, pixelColor.output().g, pixelColor.output().b));
                }
                float percentage = (static_cast<float>(y) / static_cast<float>(height)) * 100;
                cout << "\rRendering Progress: " << percentage;
            }
            glEnd();
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    //glfwTerminate();
    //ReleaseDC(consoleWindow, consoleDC);
    //cin.ignore();
    return 0;
}
