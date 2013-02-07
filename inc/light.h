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

    Vector3 getPosition();
    void    setPosition(Vector3 position);

    Colour  getColour();
    void    setColour(Colour colour);

private:
    Vector3     m_position;
    Colour      m_colour;
};

#endif
