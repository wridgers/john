#include "types/vector3.h"

Vector3::Vector3() :
  x(0.0), y(0.0), z(0.0)
{

}

Vector3::Vector3(int a, int b, int c) :
  x((double)a), y((double)b), z((double)c)
{

}

Vector3::Vector3(double a, double b, double c) :
  x(a), y(b), z(c)
{

}

Vector3::Vector3(Vector3 from, Vector3 to)
{
  x = to.x - from.x;
  y = to.y - from.y;
  z = to.z - from.z;
}

Vector3::~Vector3()
{

}

///////////////////////////////////////////////////////////////////////////

Vector3& Vector3::operator= (const Vector3 &rhs)
{
  if (this == &rhs)
    return *this;

  x = rhs.x;
  y = rhs.y;
  z = rhs.z;

  return *this;
}

Vector3 Vector3::operator+ (const Vector3 &rhs)
{
  return Vector3(
    x + rhs.x,
    y + rhs.y,
    z + rhs.z
  );
}

Vector3 Vector3::operator+ (const double &rhs)
{
  return Vector3(
    x + rhs,
    y + rhs,
    z + rhs
  );
}

Vector3 Vector3::operator+ ()
{
  return Vector3(
    x,
    y,
    z
  );
}

Vector3 Vector3::operator- (const Vector3 &rhs)
{
  return Vector3(
    x - rhs.x,
    y - rhs.y,
    z - rhs.z
  );
}

Vector3 Vector3::operator- (const double &rhs)
{
  return Vector3(
    x - rhs,
    y - rhs,
    z - rhs
  );
}

Vector3 Vector3::operator- ()
{
  return Vector3(
    - x,
    - y,
    - z
  );
}

Vector3 Vector3::operator* (const double &rhs)
{
  return Vector3(
    x * rhs,
    y * rhs,
    z * rhs
  );
}

Vector3 Vector3::operator/ (const double &rhs)
{
  assert(rhs != 0);

  double inverse = 1.0 / rhs;

  return Vector3(
    x * inverse,
    y * inverse,
    z * inverse
  );
}

Vector3& Vector3::operator+= (const Vector3 &rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;

  return *this;
}

Vector3& Vector3::operator+= (const double &rhs)
{
  x += rhs;
  y += rhs;
  z += rhs;

  return *this;
}

Vector3& Vector3::operator-= (const Vector3 &rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;

  return *this;
}

Vector3& Vector3::operator-= (const double &rhs)
{
  x -= rhs;
  y -= rhs;
  z -= rhs;

  return *this;
}

Vector3& Vector3::operator*= (const double &rhs)
{
  x *= rhs;
  y *= rhs;
  z *= rhs;

  return *this;
}

Vector3& Vector3::operator/= (const double &rhs)
{
  assert(rhs != 0);

  double inverse = 1.0 / rhs;

  x *= inverse;
  y *= inverse;
  z *= inverse;

  return *this;
}

///////////////////////////////////////////////////////////////////////////

double Vector3::dot(const Vector3 &rhs)
{
  return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vector3 Vector3::cross(const Vector3 &rhs)
{
  return Vector3(
    y*rhs.z - z*rhs.y,
    z*rhs.x - x*rhs.z,
    x*rhs.y - y*rhs.x
  );
}

double Vector3::magnitude()
{
  // TODO: optimise this
  return sqrt(x*x + y*y + z*z);
}

double Vector3::magnitudeSquare()
{
  return (x*x + y*y + z*z);
}

void Vector3::normalise()
{
  double mag = magnitude();

  assert(mag != 0);

  x /= mag;
  y /= mag;
  z /= mag;
}

void Vector3::disturb(double amount)
{
  std::random_device device;
  std::uniform_real_distribution<double> dist(-amount, amount);

  x += dist(device);
  y += dist(device);
  z += dist(device);
}

void Vector3::disturb(Vector3 amount)
{
  std::random_device device;

  std::uniform_real_distribution<double> distX(-amount.x, amount.x);
  std::uniform_real_distribution<double> distY(-amount.y, amount.y);
  std::uniform_real_distribution<double> distZ(-amount.z, amount.z);

  x += distX(device);
  y += distY(device);
  z += distZ(device);
}
