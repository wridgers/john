#ifndef __COLOUR_H__
#define __COLOUR_H__

#include <assert.h>
#include <iostream>
#include <vector>

using namespace std;

class Colour
{
  public:
    Colour();
    Colour(int r, int g, int b);
    Colour(double r, double g, double b);
    Colour(vector<Colour*> colours);

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
