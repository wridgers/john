#include "objects/triangle.h"

Triangle::Triangle()
{

}

Triangle::~Triangle()
{

}

void Triangle::setVerticies(Vector3 v0, Vector3 v1, Vector3 v2)
{
  m_v0 = v0;
  m_v1 = v1;
  m_v2 = v2;
}

pair<bool, double> Triangle::intersectionCheck(Ray& ray)
{
  return pair<bool, double> (false, 0.0);
}

Vector3 Triangle::surfaceNormal(Vector3& intersection)
{
  return Vector3();
}

