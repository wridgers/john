#include "object.h"

Object::Object()
{

}

Object::~Object()
{

}

pair<bool, double> Object::intersectionCheck(Ray& ray)
{
    return pair<bool, double> (false, 0.0);
}

Vector3 Object::surfaceNormal(Vector3& intersection)
{
    return Vector3(0, 0, 0);
}

Material* Object::getMaterial()
{
    return m_material;
}

void Object::setMaterial(Material* material)
{
    m_material = material;
}