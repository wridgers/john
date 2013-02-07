#include "light.h"

Light::Light()
{
    m_position = Vector3(0, 0, 0);
    m_colour = Colour(255, 255, 255);
}

Light::Light(Vector3 position)
    : m_position(position)
{
    m_colour = Colour(255, 255, 255);
}

Light::~Light()
{

}

Vector3 Light::getPosition()
{
    return m_position;
}

void Light::setPosition(Vector3 position)
{
    m_position = position;
}

Colour Light::getColour()
{
    return m_colour;
}

void Light::setColour(Colour colour)
{
    m_colour = colour;
}
