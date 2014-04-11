#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "core/material.h"
#include "types/vector3.h"
#include "types/ray.h"

using namespace std;

class Object
{
public:
  Object();
  ~Object();

  // mathematics functions, unique to each type of object
  virtual pair<bool, double>  intersectionCheck(Ray& ray);
  virtual Vector3             surfaceNormal(Vector3& intersection);

  Material*   getMaterial();
  void        setMaterial(Material* material);

protected:
  Material*   m_material;

};

#endif