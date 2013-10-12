#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <assert.h>
#include <cmath>
#include <iostream>

using namespace std;

class Vector3
{
  public:
    Vector3();
    Vector3(int a, int b, int c);
    Vector3(double a, double b, double c);
    Vector3(Vector3 from, Vector3 to);
    ~Vector3();

    // actual values
    double x, y, z;

    // assignment operator
    Vector3& operator= (const Vector3 &rhs);

    // binary arithmetic operators
    Vector3 operator+ (const Vector3 &rhs);
    Vector3 operator+ (const double &rhs);
    Vector3 operator+ ();

    Vector3 operator- (const Vector3 &rhs);
    Vector3 operator- (const double &rhs);
    Vector3 operator- ();

    Vector3 operator* (const double &rhs);
    Vector3 operator/ (const double &rhs);

    // compound assignment operators
    Vector3& operator+= (const Vector3 &rhs);
    Vector3& operator+= (const double &rhs);
    Vector3& operator-= (const Vector3 &rhs);
    Vector3& operator-= (const double &rhs);
    Vector3& operator*= (const double &rhs);
    Vector3& operator/= (const double &rhs);

    // comparison operators
    bool operator== (const Vector3 &rhs);
    bool operator!= (const Vector3 &rhs);

    // vector arithmetic
    double      dot(const Vector3 &rhs);
    Vector3     cross(const Vector3 &rhs);

    double      magnitude();
    double      magnitudeSquare();
    void        normalise();

};

// typedefs for future expansion
typedef Vector3 Vector3d;
typedef Vector3 Vector3f;

#endif
