#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "colour.h"
#include "vector3.h"

using namespace std;

class Light
{
public:
    Light();
    Light(Vector3 pos);
    ~Light();

    Vector3 getPosition();
    void    setPosition(Vector3 pos);

    Colour  getColour();
    void    setColour(Colour col);

private:
    Vector3     position;
    Colour      colour;
};

#endif
