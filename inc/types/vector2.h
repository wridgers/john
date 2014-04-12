#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <assert.h>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

class Vector2
{
public:
  Vector2();
  Vector2(int a, int b);
  Vector2(double a, double b);
  Vector2(Vector2 from, Vector2 to);
  ~Vector2();

  // actual values
  double x, y;

  // assignment operator
  Vector2& operator= (const Vector2 &rhs);

  // binary arithmetic operators
  Vector2 operator+ (const Vector2 &rhs);
  Vector2 operator+ (const double &rhs);
  Vector2 operator+ ();

  Vector2 operator- (const Vector2 &rhs);
  Vector2 operator- (const double &rhs);
  Vector2 operator- ();

  Vector2 operator* (const double &rhs);
  Vector2 operator/ (const double &rhs);

  // compound assignment operators
  Vector2& operator+= (const Vector2 &rhs);
  Vector2& operator+= (const double &rhs);
  Vector2& operator-= (const Vector2 &rhs);
  Vector2& operator-= (const double &rhs);
  Vector2& operator*= (const double &rhs);
  Vector2& operator/= (const double &rhs);

  // comparison operators
  bool operator== (const Vector2 &rhs);
  bool operator!= (const Vector2 &rhs);

  // vector arithmetic
  double      dot(const Vector2 &rhs);
  Vector2     cross(const Vector2 &rhs);

  // other vector operations
  double      magnitude();
  double      magnitudeSquare();
  void        normalise();

  // randomise
  void        disturb(double amount);
  void        disturb(Vector2 amount);

};

// typedefs for future expansion
typedef Vector2 Vector2d;
typedef Vector2 Vector2f;

#endif
