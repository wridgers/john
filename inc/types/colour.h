#ifndef __COLOUR_H__
#define __COLOUR_H__

#include <iostream>

class Colour
{
  public:
    Colour();
    Colour(int r, int g, int b);
    Colour(double r, double g, double b);

    // TODO: create colour from array/vector of colours (arithmetic average)
    // TODO: finish operators

    ~Colour();

    // public information
    double m_red, m_green, m_blue;

    // assignment operator

    // binary arithmetic operators
    Colour  operator+ (const Colour &rhs);

    Colour  operator* (const double &rhs);

    // compound assignment operators
    Colour& operator+= (const Colour &rhs);
    Colour& operator+= (const double &rhs);

    // comparison operators

    // for image output
    int getRedRGB();
    int getGreenRGB();
    int getBlueRGB();
};

#endif
