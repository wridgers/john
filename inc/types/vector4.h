#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include <assert.h>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

class Vector4
{
public:
  Vector4();
  Vector4(int a, int b, int c, int d);
  Vector4(double a, double b, double c, double d);
  Vector4(Vector4 from, Vector4 to);
  ~Vector4();

  // actual values
  double w, x, y, z;

  // assignment operator
  Vector4& operator= (const Vector4 &rhs);

  // binary arithmetic operators
  Vector4 operator+ (const Vector4 &rhs);
  Vector4 operator+ (const double &rhs);
  Vector4 operator+ ();

  Vector4 operator- (const Vector4 &rhs);
  Vector4 operator- (const double &rhs);
  Vector4 operator- ();

  Vector4 operator* (const double &rhs);
  Vector4 operator/ (const double &rhs);

  // compound assignment operators
  Vector4& operator+= (const Vector4 &rhs);
  Vector4& operator+= (const double &rhs);
  Vector4& operator-= (const Vector4 &rhs);
  Vector4& operator-= (const double &rhs);
  Vector4& operator*= (const double &rhs);
  Vector4& operator/= (const double &rhs);

  // comparison operators
  bool operator== (const Vector4 &rhs);
  bool operator!= (const Vector4 &rhs);

  // vector arithmetic
  double      dot(const Vector4 &rhs);
  Vector4     cross(const Vector4 &rhs);

  // other vector operations
  double      magnitude();
  double      magnitudeSquare();
  void        normalise();

  // randomise
  void        disturb(double amount);
  void        disturb(Vector4 amount);

};

// typedefs for future expansion
typedef Vector4 Vector4d;
typedef Vector4 Vector4f;

#endif
