#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "World.h"

using namespace std;

HWND consoleWindow = GetConsoleWindow();

int main()
{
    HDC consoleDC = GetDC(consoleWindow);

    int width = 200;
    int height = 200;
    int zoom = 20;

    Vector sphere1Location = Vector(0, 0, 10);
    Sphere sphere1 = Sphere(sphere1Location, .1);
    Vector sphere2Location = Vector(0, .1, 10);
    Sphere sphere2 = Sphere(sphere2Location, .1);
    vector <Sphere> spheres;
    spheres.push_back(sphere1);
    spheres.push_back(sphere2);
    World world = World(spheres);

    Vector origin = Vector(0, 0, 0);
    Vector direction = Vector(0, 0, 0);
    Ray cameraRay = Ray(origin, direction);
    int frame = 0;
    for (int i = 0; i < 500; i++) {
        frame++;
        world.spheres.at(0).center.x = sin(frame / 10.0)/8.0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cameraRay.direction = Vector((x - width / 2.0f) / width, (-y + height / 2.0f) / height, zoom);
                if (world.distanceAlongRay(cameraRay) > 0) {
                    SetPixelV(consoleDC, x*2, y*2, RGB(255, 255, 255));
                }
                else {
                    SetPixelV(consoleDC, x*2, y*2, RGB(0, 0, 0));
                }
            }
        }
    }

    ReleaseDC(consoleWindow, consoleDC);
    cin.ignore();
    return 0;
}
