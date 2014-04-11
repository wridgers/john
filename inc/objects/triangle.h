#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "core/object.h"
#include "types/ray.h"
#include "types/vector3.h"

using namespace std;

class Triangle : public Object
{
public:
    Triangle();
    ~Triangle();

    // set position
    void setVerticies(Vector3 v0, Vector3 v1, Vector3 v2);

    // object maths
    pair<bool, double>  intersectionCheck(Ray& ray);
    Vector3             surfaceNormal(Vector3& intersection);

private:
    Vector3     m_v0, m_v1, m_v2;
};

#endif
