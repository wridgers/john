#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__


#include "maths/vector3.h"
#include "objects/object.h"
#include "types/ray.h"

using namespace std;

class Triangle : public Object
{
public:
    Triangle();
    ~Triangle();

    // object maths
    pair<bool, double>  intersectionCheck(Ray& ray);
    Vector3             surfaceNormal(Vector3& intersection);

private:
    Vector3     v0, v1, v2;
};

#endif