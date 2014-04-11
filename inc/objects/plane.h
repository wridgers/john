#ifndef __PLANE_H__
#define __PLANE_H__

#include "core/material.h"
#include "core/object.h"
#include "types/ray.h"
#include "types/vector3.h"

using namespace std;

class Plane : public Object
{
public:
  Plane();
  Plane(Vector3 position, Vector3 normal);
  ~Plane();

  void setNormal(Vector3 normal);
  void setPosition(Vector3 position);

  void setWidth(double width);
  void setLength(double length);

  // object maths
  pair<bool, double>  intersectionCheck(Ray& ray);
  Vector3             surfaceNormal(Vector3& intersection);

private:
  Vector3     m_normal, m_position;

  double      m_width, m_length;
};

#endif
