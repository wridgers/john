#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <iostream>
#include <cmath>

using namespace std;

class Vector3
{
public:
	Vector3();
	Vector3(int a, int b, int c);
	Vector3(double a, double b, double c);
	~Vector3();

	// actual values
	double x, y, z;

	// overloads
	friend const Vector3 operator+ (const Vector3 &lhs, const Vector3 &rhs);
	friend const Vector3 operator- (const Vector3 &lhs, const Vector3 &rhs);
	friend const Vector3 operator* (const Vector3 &lhs, double rhs);
	friend const Vector3 operator/ (const Vector3 &lhs, double rhs);

	friend ostream& operator<<	(ostream &os, const Vector3 &rhs);

	// vector arithmetic
	double	dot(const Vector3 &rhs);
	Vector3 cross(const Vector3 &rhs);

	double  magnitude();
	double	magnitudeSquare();
	void	normalise();

};

// typedefs for future expansion (Vector3f for example)
typedef Vector3 Vector3d;

#endif