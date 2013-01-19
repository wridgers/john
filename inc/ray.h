#ifndef __RAY_H__
#define __RAY_H__

#include "vector3.h"

class Ray
{
public:
	Ray(Vector3 origin, Vector3 direction);
	~Ray();

    Vector3 at(double t);

private:
	Vector3 origin, direction;
};

#endif