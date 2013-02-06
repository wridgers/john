#include "ray.h"

Ray::Ray(Vector3 origin, Vector3 direction)
{
    // r = o + t*d
    Ray::origin = origin;
    Ray::direction = direction;
}

Ray::~Ray()
{

}

Vector3 Ray::getOrigin()
{
    return Ray::origin;
}

void Ray::setOrigin(Vector3 origin)
{
    Ray::origin = origin;
}

Vector3 Ray::getDirection()
{
    return Ray::direction;
}

void Ray::setDirection(Vector3 direction)
{
    Ray::direction = direction;
}

Vector3 Ray::at(double t)
{
    Vector3 point = Ray::origin + (Ray::direction * t);
    return point;
}