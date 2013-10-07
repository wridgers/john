#include "types/colour.h"

Colour::Colour()
{
  m_red     = 0.0;
  m_green   = 0.0;
  m_blue    = 0.0;
}

Colour::Colour(int r, int g, int b)
{
  m_red     = (double)r;
  m_green   = (double)g;
  m_blue    = (double)b;
}

Colour::Colour(double r, double g, double b) {
  m_red     = r;
  m_green   = g;
  m_blue    = b;
}

// TODO: this function is probably really slow. I need to lookup the size of
// the vector in a smart way, but I'm currently on the train and have no
// documentation with me (nor internet access). Also it'd be faster to have a
// vector of references as opposed to actual objects. I should probably add
// another constructor that lets you pass an array of pointers too.
Colour::Colour(vector<Colour*> colours) {
  m_red     = 0.0;
  m_green   = 0.0;
  m_blue    = 0.0;

  int total = 0;

  for (auto colour : colours) {
    m_red   += colour->m_red;
    m_green += colour->m_green;
    m_blue  += colour->m_blue;

    total++;
  }

  m_red   /= total; 
  m_green /= total; 
  m_blue  /= total; 
}

Colour::~Colour()
{

}

///////////////////////////////////////////////////////////////////////////

Colour Colour::operator= (const Colour &rhs)
{
  if (this == &rhs)
    return *this;

  m_red = rhs.m_red;
  m_green = rhs.m_green;
  m_blue = rhs.m_blue;

  return *this;
}

Colour Colour::operator+ (const Colour &rhs)
{
  return Colour(
    m_red     + rhs.m_red,
    m_green   + rhs.m_green,
    m_blue    + rhs.m_blue
  );
}

Colour Colour::operator+ (const double &rhs)
{
  return Colour(
    m_red     + rhs,
    m_green   + rhs,
    m_blue    + rhs
  );
}

Colour Colour::operator+ ()
{
  return Colour(
    m_red,
    m_green,
    m_blue 
  );
}

Colour Colour::operator- (const Colour &rhs)
{
  return Colour(
    m_red     - rhs.m_red,
    m_green   - rhs.m_green,
    m_blue    - rhs.m_blue
  );
}

Colour Colour::operator- (const double &rhs)
{
  return Colour(
    m_red     - rhs,
    m_green   - rhs,
    m_blue    - rhs
  );
}

Colour Colour::operator- ()
{
  return Colour(
    - m_red,
    - m_green,
    - m_blue 
  );
}

Colour Colour::operator* (const double &rhs)
{
  return Colour(
    m_red     * rhs,
    m_green   * rhs,
    m_blue    * rhs
  );
}

Colour Colour::operator/ (const double &rhs)
{
  assert(rhs != 0);

  return Colour(
    m_red     / rhs,
    m_green   / rhs,
    m_blue    / rhs
  );
}

Colour& Colour::operator+= (const Colour &rhs)
{
  m_red     += rhs.m_red;
  m_green   += rhs.m_green;
  m_blue    += rhs.m_blue;

  return *this;
}

Colour& Colour::operator+= (const double &rhs)
{
  m_red     += rhs;
  m_green   += rhs;
  m_blue    += rhs;

  return *this;
}

Colour& Colour::operator-= (const Colour &rhs)
{
  m_red     -= rhs.m_red;
  m_green   -= rhs.m_green;
  m_blue    -= rhs.m_blue;

  return *this;
}

Colour& Colour::operator-= (const double &rhs)
{
  m_red     -= rhs;
  m_green   -= rhs;
  m_blue    -= rhs;

  return *this;
}

Colour& Colour::operator*= (const double &rhs)
{
  m_red     *= rhs;
  m_green   *= rhs;
  m_blue    *= rhs;

  return *this;
}

Colour& Colour::operator/= (const double &rhs)
{
  assert(rhs != 0);

  m_red     /= rhs;
  m_green   /= rhs;
  m_blue    /= rhs;

  return *this;
}

int Colour::getRedRGB()
{
  int red = (int)m_red;

  if (red < 0) return 0;
  if (red > 255) return 255;

  return red;
}

int Colour::getGreenRGB()
{
  int green = (int)m_green;

  if (green < 0) return 0;
  if (green > 255) return 255;

  return green;
}

int Colour::getBlueRGB()
{
  int blue = (int)m_blue;

  if (blue < 0) return 0;
  if (blue > 255) return 255;

  return blue;
}
