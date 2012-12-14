#include "ray.h"

Ray::Ray(Vector3d o, Vector3d d)
{
	// r = o + t*d
	origin = o;
	direction = d;
}

Ray::~Ray()
{

}