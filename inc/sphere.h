#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "material.h"
#include "vector3.h"

class Sphere
{
public:
    Sphere();
    Sphere(Vector3 pos, double rad);
    ~Sphere();

    double      getRadius();
    void        setRadius(double rad);

    Vector3     getPosition();
    void        setPosition(Vector3 pos);

    Material*   getMaterial();
    void        setMaterial(Material *mat);

private:
    double      radius;
    Vector3     position;

    Material    *material;
};

#endif
