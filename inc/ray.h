#ifndef __RAY_H__
#define __RAY_H__

#include "vector3.h"

class Ray
{
public:
	Ray(Vector3 origin, Vector3 direction);
	~Ray();

    Vector3 getOrigin();
    void    setOrigin(Vector3 origin);

    Vector3 getDirection();
    void    setDirection(Vector3 direction);

    Vector3 at(double t);
private:
	Vector3 origin, direction;
};

#endif