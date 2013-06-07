#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "colour.h"
#include "vector3.h"

using namespace std;

class Light
{
public:
    Light();
    Light(Vector3 position);
    ~Light();

    Colour  getColour();
    void    setColour(Colour colour);

    double  getIntensity();
    void    setIntensity(double intensity);

    Vector3 getPosition();
    void    setPosition(Vector3 position);

private:
    Colour      m_colour;
    double      m_intensity;
    Vector3     m_position;
};

#endif
