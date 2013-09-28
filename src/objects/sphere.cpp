#include "objects/sphere.h"

Sphere::Sphere()
{
    this->m_position    = Vector3(0,0,0);
    this->m_radius      = 100.0f;
}

Sphere::Sphere(Vector3 position, double radius)
    : m_position(position), m_radius(radius)
{

}

Sphere::~Sphere()
{

}

void Sphere::setPosition(Vector3 position)
{
    m_position = position;
}

void Sphere::setRadius(double radius)
{
    m_radius = radius;
}

pair<bool, double> Sphere::intersectionCheck(Ray& ray)
{
    // make calculation a bit easier
    Vector3 oMinusC = ray.getOrigin() - m_position;

    // find a,b,c for quadratic formula
    // double a = rayDirection.dot(rayDirection);
    //          = 1
    double b = 2*ray.getDirection().dot(oMinusC);
    double c = oMinusC.dot(oMinusC) - (m_radius*m_radius);

    // we check the discriminant to see if there is an intersection
    double discriminant = (b*b) - 4*c;

    if (discriminant > 0) {
        // yes! intersection!

        // find the two solutions (we know there are two, because discriminant > 0)
        double t1 = (- b + sqrt(discriminant)) * 0.5;
        double t2 = (- b - sqrt(discriminant)) * 0.5;

        // we find the closest (smallest) one
        double t = t1;
        if (t2 < t1) t = t2;

        // return yes and closest t
        return pair<bool, double> (true, t);
    }

    return pair<bool, double> (false, 0.0);
}

Vector3 Sphere::surfaceNormal(Vector3& intersection) 
{
    Vector3 normal(m_position, intersection);
    normal.normalise();

    return normal;
}