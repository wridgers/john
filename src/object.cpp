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
    return Object::material;
}

void Object::setMaterial(Material* mat)
{
    Object::material = mat;
}