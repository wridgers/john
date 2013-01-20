#include "object.h"

Object::Object()
{

}

Object::~Object()
{

}

Material* Object::getMaterial()
{
    return Object::material;
}

void Object::setMaterial(Material* mat)
{
    Object::material = mat;
}