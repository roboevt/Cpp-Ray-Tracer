// Ray Tracer MK2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <math.h>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"

using namespace std;

HWND consoleWindow = GetConsoleWindow();

int main()
{
    HDC consoleDC = GetDC(consoleWindow);

    int width = 400;
    int height = 400;
    int zoom = 30;

    Vector sphereLocation = Vector(0, 0, 10);
    Sphere sphere = Sphere(sphereLocation, .1);
    Vector origin = Vector(0, 0, 0);

    Vector direction = Vector(0, 0, 0);
    Ray cameraRay = Ray(origin, direction);
    int frame = 0;
    for (int i = 0; i < 500; i++) {
        frame++;
        sphere.center.x = sin(frame / 10.0)/8.0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cameraRay.direction = Vector((x - width / 2.0f) / width, (y - height / 2.0f) / height, zoom);
                if (sphere.distanceAlongRay(cameraRay) > 0) {
                    SetPixel(consoleDC, x, y, RGB(255, 255, 255));
                }
                else {
                    SetPixel(consoleDC, x, y, RGB(0, 0, 0));
                }
            }
        }
    }

        ReleaseDC(consoleWindow, consoleDC);
        cin.ignore();
        return 0;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
