#include "light.h"

Light::Light()
{
    Light::position = Vector3(0, 0, 0);
    Light::colour = Colour(255, 255, 255);
}

Light::Light(Vector3 pos)
    : position(pos)
{
    Light::colour = Colour(255, 255, 255);
}

Light::~Light()
{

}

Vector3 Light::getPosition()
{
    return Light::position;
}

void Light::setPosition(Vector3 pos)
{
    Light::position = pos;
}

Colour Light::getColour()
{
    return Light::colour;
}

void Light::setColour(Colour col)
{
    Light::colour = col;
}
