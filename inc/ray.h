#ifndef __RAY_H__
#define __RAY_H__

#include "vector3.h"

class Ray
{
public:
	Ray(Vector3d o, Vector3d d);
	~Ray();

private:
	Vector3d origin, direction;
};

#endif