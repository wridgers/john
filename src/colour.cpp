#include "colour.h"

Colour::Colour()
{
	Colour::red     = 0.0;
	Colour::green   = 0.0;
	Colour::blue    = 0.0;
}

Colour::Colour(int r, int g, int b)
{
	Colour::red     = (double)r;
	Colour::green   = (double)g;
	Colour::blue    = (double)b;
}

Colour::Colour(double r, double g, double b) {
	Colour::red     = r;
	Colour::green   = g;
	Colour::blue    = b;
}

Colour::~Colour()
{

}

Colour Colour::operator* (const double &rhs)
{
    return Colour(
        Colour::red     * rhs,
        Colour::green   * rhs,
        Colour::blue    * rhs
    );
}

Colour& Colour::operator+= (const Colour &rhs)
{
    Colour::red     += rhs.red;
    Colour::green   += rhs.green;
    Colour::blue    += rhs.blue;

    return *this;
}

Colour& Colour::operator+= (const double &rhs)
{
    Colour::red     += rhs;
    Colour::green   += rhs;
    Colour::blue    += rhs;

    return *this;
}

int Colour::getRedRGB()
{
    int red = (int)Colour::red;

    if (red < 0) return 0;
    if (red > 255) return 255;

    return red;
}

int Colour::getGreenRGB()
{
    int green = (int)Colour::green;

    if (green < 0) return 0;
    if (green > 255) return 255;

    return green;
}

int Colour::getBlueRGB()
{
    int blue = (int)Colour::blue;

    if (blue < 0) return 0;
    if (blue > 255) return 255;

    return blue;
}