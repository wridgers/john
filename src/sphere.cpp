#include "sphere.h"

Sphere::Sphere()
{
    Sphere::position    = Vector3(0,0,0);
    Sphere::radius      = 100.0f;
}

Sphere::Sphere(Vector3 pos, double rad)
    : position(pos), radius(rad)
{
}

Sphere::~Sphere()
{

}

Vector3 Sphere::getPosition()
{
    return Sphere::position;
}

void Sphere::setPosition(Vector3 pos)
{
    Sphere::position = pos;
}

double Sphere::getRadius()
{
    return Sphere::radius;
}

void Sphere::setRadius(double rad)
{
    Sphere::radius = rad;
}

Material* Sphere::getMaterial()
{
    return Sphere::material;
}

void Sphere::setMaterial(Material *mat)
{
    Sphere::material = mat;
}
