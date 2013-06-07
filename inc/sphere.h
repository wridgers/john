#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "material.h"
#include "object.h"
#include "ray.h"
#include "vector3.h"

using namespace std;

class Sphere : public Object
{
public:
    Sphere();
    Sphere(Vector3 position, double radius);
    ~Sphere();

    // we only need setters here
    void setPosition(Vector3 position);
    void setRadius(double radius);

    // object maths
    pair<bool, double>  intersectionCheck(Ray& ray);
    Vector3             surfaceNormal(Vector3& intersection);

private:
    double      m_radius;
    Vector3     m_position;
};

#endif
