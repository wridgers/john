#include "ray.h"

Ray::Ray(Vector3 origin, Vector3 direction)
    : m_origin(origin), m_direction(direction)
{
}

Ray::~Ray()
{

}

Vector3 Ray::getOrigin()
{
    return m_origin;
}

void Ray::setOrigin(Vector3 origin)
{
    origin = origin;
}

Vector3 Ray::getDirection()
{
    return m_direction;
}

void Ray::setDirection(Vector3 direction)
{
    direction = direction;
}

Vector3 Ray::at(double t)
{
    return m_origin + (m_direction * t);
}