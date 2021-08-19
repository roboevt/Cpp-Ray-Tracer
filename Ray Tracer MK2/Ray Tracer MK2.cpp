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
#include "Material.h"

using namespace std;

HWND consoleWindow = GetConsoleWindow();

int main()
{
    HDC consoleDC = GetDC(consoleWindow);

    int width = 200;
    int height = 200;
    int samples = 5;
    int zoom = 20;

    Vector sphere1Location = Vector(0, 0, 10);
    Material sphere1Mat;
    sphere1Mat.color = Color(255, 0, 0);
    Sphere sphere1 = Sphere(sphere1Location, .05, sphere1Mat);
    Vector sphere2Location = Vector(0, .1, 10);
    Material sphere2Mat;
    sphere2Mat.color = Color(0, 0, 255);
    Sphere sphere2 = Sphere(sphere2Location, .08, sphere2Mat);
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
        world.spheres.at(0).center.x = sin(frame / 10.0)/6.0;
        world.spheres.at(1).center.y = sin(frame / 15.0) / 6.0;
        world.spheres.at(0).center.z = cos(frame / 10.0) / .2 + 10;
        collision.point = origin;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cameraRay.direction = Vector((x - width / 2.0f) / width, (-y + height / 2.0f) / height, zoom);
                collision.point = cameraRay.origin;
                collision.outVector = cameraRay.direction;
                collision.remainingBounces = 1;
                collision.color = Color(0, 0, 0);
                Color pixelColor = Color(0, 0, 0);
                for (int s = 0; s < samples; s++) {
                    pixelColor = pixelColor + world.calcNextCollision(collision).color;
                }
                SetPixel(consoleDC, x*2, y*2+50, RGB(pixelColor.output().r, pixelColor.output().g, pixelColor.output().b));
            }
        }
    }

    ReleaseDC(consoleWindow, consoleDC);
    cin.ignore();
    return 0;
}
