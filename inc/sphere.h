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
    Sphere(Vector3 pos, double rad);
    ~Sphere();

    // we only need setters here
    void        setRadius(double rad);
    void        setPosition(Vector3 pos);

    // object maths
    pair<bool, double>  intersectionCheck(Ray& ray);
    Vector3             surfaceNormal(Vector3& intersection);

private:
    double      radius;
    Vector3     position;
};

#endif
