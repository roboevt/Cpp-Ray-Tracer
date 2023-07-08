#include "World.h"

#include <random>

World::World(std::vector<Sphere> spheres) {
    this->spheres = spheres;
}

Color World::calcColor(Ray& ray, int remainingBounces) const {
    if (remainingBounces == 0) {  // no bounces left (base case)
        return Color(0, 0, 0);
    }
    Collision collision;
    collision.outVector = ray.direction;
    if (hit(ray, collision)) {
        if (collision.hitObject.material.shader == emmisive) {
            return collision.hitObject.material.color;
        }
        collision.normal = (collision.point - collision.hitObject.center).normalized();  // should probably be normalized
        collision.inVector = collision.outVector;
        collision.outVector = calcBounce(collision);
        Ray nextRay = Ray(collision.point, collision.outVector);
        Color rayColor = calcColor(nextRay, remainingBounces - 1);
        return collision.hitObject.material.color + calcColor(nextRay, remainingBounces - 1) * collision.absorbtion;  // This is wrong because of the +. It will always return the objects color, even if there is no light.
    }
    return this->backgroundColor;
}

bool World::hit(Ray& ray, Collision& collision) const {
    float closest = std::numeric_limits<float>::max();
    bool hitAnything = false;
    for (const Sphere& sphere : this->spheres) {
        float distance = sphere.distanceAlongRay(ray);
        if (distance > 0 && distance < closest) {
            hitAnything = true;
            closest = distance;
            collision.hitObject = sphere;
            collision.point = ray.at(distance);
        }
    }
    return hitAnything;
}

Vector World::calcBounce(Collision& collision) const {
    if (collision.hitObject.material.shader == diffuse) {
        collision.absorbtion = collision.hitObject.material.absorbtion;
        return (collision.normal + randomInUnitSphere()).normalized();
    }
    if (collision.hitObject.material.shader == reflective) {
        collision.absorbtion = 1;
        return collision.inVector - (collision.normal * 2 * collision.inVector.dot(collision.normal));
    }
    return Vector(0, 0, 1);
}

Vector World::randomInUnitSphere() const {
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_real_distribution<float> distribution(-1.0, 1.0);
    Vector test = Vector(1, 1, 1);
    // while (test.magnitudeSquared() > 1.0) {  // Making sure the vector is in the unit sphere is techincally correct but adds around 20-30% to frame times.
    float x = distribution(generator);
    float y = distribution(generator);
    float z = distribution(generator);
    test = Vector(x, y, z);
    //}
    return test.normalized();
}