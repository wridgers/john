#ifndef __COLOUR_H__
#define __COLOUR_H__

#include <iostream>

class Colour
{
public:
	Colour();
	Colour(int r, int g, int b);
	Colour(double r, double g, double b);
	~Colour();

    // public information
	double m_red, m_green, m_blue;

    // operators
	Colour  operator*  (const double &rhs);
    Colour& operator+= (const Colour &rhs);
    Colour& operator+= (const double &rhs);

    // for image output
    int getRedRGB();
    int getGreenRGB();
    int getBlueRGB();
};

#endif
