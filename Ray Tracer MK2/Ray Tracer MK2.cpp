#include <iostream>
#include <Windows.h>
#include <math.h>
#include <vector>
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "World.h"
#include "Collision.h"
#include "Color.h"

using namespace std;

HWND consoleWindow = GetConsoleWindow();

int main()
{
    HDC consoleDC = GetDC(consoleWindow);

    int width = 200;
    int height = 200;
    int samples = 1;
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
    Collision collision;
    int frame = 0;
    for (int i = 0; i < 500; i++) {
        cout << frame << " ";
        frame++;
        world.spheres.at(0).center.x = sin(frame / 10.0)/8.0;
        collision.point = origin;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cameraRay.direction = Vector((x - width / 2.0f) / width, (-y + height / 2.0f) / height, zoom);
                collision.point = cameraRay.origin;
                collision.outVector = cameraRay.direction;
                collision.remainingBounces = 1;
                collision.color = Color(0, 0, 0);
                //Color pixelColor = Color(0, 0, 0);
                //for (int s = 0; s < samples; s++) {
                //    pixelColor = pixelColor + world.calcNextCollision(collision).color;
                //}
                //SetPixel(consoleDC, x, y+50, RGB(pixelColor.output().r, pixelColor.output().g, pixelColor.output().b));

                //if (world.spheres.at(0).distanceAlongRay(cameraRay) != 0) {
                //    SetPixel(consoleDC, x, y + 50, RGB(255,255,255));
                //}
                //else {
                //    SetPixel(consoleDC, x, y + 50, RGB(0, 0, 0));
                //}

                Color pixelColor = world.calcNextCollision(collision).color;
                SetPixel(consoleDC, x, y + 50, RGB(pixelColor.r, pixelColor.g, pixelColor.b));
            }
        }
    }

    ReleaseDC(consoleWindow, consoleDC);
    cin.ignore();
    return 0;
}
