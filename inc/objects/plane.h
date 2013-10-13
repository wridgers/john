#ifndef __PLANE_H__
#define __PLANE_H__

#include "materials/material.h"
#include "maths/vector3.h"
#include "objects/object.h"
#include "types/ray.h"

using namespace std;

class Plane : public Object
{
public:
  Plane();
  Plane(Vector3 position, Vector3 normal);
  ~Plane();

  // we only need setters here
  void setNormal(Vector3 normal);
  void setPosition(Vector3 position);

  // object maths
  pair<bool, double>  intersectionCheck(Ray& ray);
  Vector3             surfaceNormal(Vector3& intersection);

private:
  Vector3     m_normal, m_position;
};

#endif