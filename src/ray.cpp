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

Vector3 Ray::at(double t)
{
    Vector3 point = Ray::origin + (Ray::direction * t);
    return point;
}