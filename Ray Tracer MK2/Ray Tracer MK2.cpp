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

    int width = 400;
    int height = 400;
    int samples = 150;
    int zoom = 20;

    Vector sphere1Location = Vector(0, 0, 10);
    Color sphere1Color = Color(255, 255, 255);
    Sphere sphere1 = Sphere(sphere1Location, .1, sphere1Color);
    sphere1.shader = 1;
    Vector sphere2Location = Vector(0, -1, 10);
    Color sphere2Color = Color(255, 255, 255);
    Sphere sphere2 = Sphere(sphere2Location, .9, sphere2Color);
    sphere2.shader = 1;
    vector <Sphere> spheres;
    spheres.push_back(sphere1);
    spheres.push_back(sphere2);
    World world = World(spheres);

    Vector origin = Vector(0, 0, 0);
    Vector direction = Vector(0, 0, 0);
    Ray cameraRay = Ray(origin, direction);
    Collision collision;
    int frame = 0;
    for (int i = 0; i < 100; i++) {
        frame++;
        //world.spheres.at(0).center.x = sin(frame / 10.0)/6.0;
        //world.spheres.at(1).center.y = sin(frame / 15.0) / 6.0;
        //world.spheres.at(0).center.z = cos(frame / 10.0) / .2 + 10;
        //collision.point = origin;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cameraRay.direction = Vector((x - width / 2.0f) / width, (-y + height / 2.0f) / height, zoom);
                collision.point = cameraRay.origin;
                collision.outVector = cameraRay.direction;
                collision.remainingBounces = 4;
                collision.color = Color(0, 0, 0);
                Color pixelColor = Color(0, 0, 0);
                for (int s = 0; s < samples; s++) {
                    //cout << pixelColor.samples << "  ";
                    pixelColor = pixelColor + world.calcNextCollision(collision).color;
                }
                SetPixel(consoleDC, x, y, RGB(pixelColor.output().r, pixelColor.output().g, pixelColor.output().b));
            }
        }
    }

    ReleaseDC(consoleWindow, consoleDC);
    cin.ignore();
    return 0;
}
