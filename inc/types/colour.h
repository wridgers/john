#ifndef __COLOUR_H__
#define __COLOUR_H__

#include <assert.h>
#include <iostream>

class Colour
{
  public:
    Colour();
    Colour(int r, int g, int b);
    Colour(double r, double g, double b);

    // TODO: create colour from array/vector of colours (arithmetic average)
    Colour(Colour *colours);

    // TODO: finish operators

    ~Colour();

    // public information
    double m_red, m_green, m_blue;

    // assignment operator
    Colour operator= (const Colour &rhs);

    // binary arithmetic operators
    Colour  operator+ (const Colour &rhs);
    Colour  operator+ (const double &rhs);
    Colour  operator+ ();

    Colour  operator- (const Colour &rhs);
    Colour  operator- (const double &rhs);
    Colour  operator- ();

    Colour  operator* (const double &rhs);
    Colour  operator/ (const double &rhs);

    // compound assignment operators
    Colour& operator+= (const Colour &rhs);
    Colour& operator+= (const double &rhs);
    Colour& operator-= (const Colour &rhs);
    Colour& operator-= (const double &rhs);
    Colour& operator*= (const double &rhs);
    Colour& operator/= (const double &rhs);

    // comparison operators
    bool operator== (const Colour &rhs);
    bool operator!= (const Colour &rhs);

    // for image output
    int getRedRGB();
    int getGreenRGB();
    int getBlueRGB();
};

#endif
