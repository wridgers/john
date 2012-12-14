#include "vector3.h"

Vector3::Vector3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3::Vector3(int a, int b, int c)
{
	x = (double)a;
	y = (double)b;
	z = (double)c;
}

Vector3::Vector3(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

Vector3::~Vector3()
{

}

const Vector3 operator+ (const Vector3 &lhs, const Vector3 &rhs)
{
	return Vector3(
		lhs.x + rhs.x,
		lhs.y + rhs.y,
		lhs.z + rhs.z
	);
}

const Vector3 operator- (const Vector3 &lhs, const Vector3 &rhs)
{
	return Vector3(
		lhs.x - rhs.x,
		lhs.y - rhs.y,
		lhs.z - rhs.z
	);
}

const Vector3 operator* (const Vector3 &lhs, double rhs)
{
	return Vector3(
		lhs.x * rhs,
		lhs.y * rhs,
		lhs.z * rhs
	);
}

const Vector3 operator/ (const Vector3 &lhs, double rhs)
{
	return Vector3(
		lhs.x / rhs,
		lhs.y / rhs,
		lhs.z / rhs
	);
}

ostream& operator<< (ostream &os, const Vector3 &rhs)
{
	os << '(' << rhs.x << ',' << rhs.y << ',' << rhs.z << ')';
	return os;
}

double Vector3::dot(const Vector3 &rhs)
{
	return x*rhs.x + y*rhs.y + z*rhs.z;
}

Vector3 Vector3::cross(const Vector3 &rhs)
{
	return Vector3(
		y*rhs.z - z*rhs.y,
		-(x*rhs.z - z*rhs.x),
		x*rhs.y - y*rhs.x
	);
}

double Vector3::magnitude()
{
	// SSE? Carmack reverse
	return sqrt(x*x + y*y + z*z);
}

double Vector3::magnitudeSquare()
{
	return x*x + y*y + z*z;
}

void Vector3::normalise()
{
	double mag = magnitude();

	x /= mag;
	y /= mag;
	z /= mag;
}