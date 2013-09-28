#include "objects/plane.h"

Plane::Plane()
{

}

Plane::Plane(Vector3 position, Vector3 normal)
    : m_position(position), m_normal(normal)
{

}

Plane::~Plane()
{

}

void Plane::setNormal(Vector3 normal)
{
    m_normal = normal;
}

void Plane::setPosition(Vector3 position)
{
    m_position = position;
}

pair<bool, double> Plane::intersectionCheck(Ray& ray)
{
    // check ray is not parallel to plane
    double dotProduct = ray.getDirection().dot(m_normal);

    if (dotProduct == 0)
        return pair<bool, double> (false, 0.0);

    // find t
    double t = (m_position.dot(m_normal) - ray.getOrigin().dot(m_normal)) / dotProduct;

    // intersection?
    if (t > 0)
        return pair<bool, double> (true, t);

    // no luck!
    return pair<bool, double> (false, 0.0);
}

Vector3 Plane::surfaceNormal(Vector3& intersection)
{
    // always the same, nice and easy
    return m_normal;
}