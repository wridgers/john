#include "vector3.h"

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

    Vector3::x = rhs.x;
    Vector3::y = rhs.y;
    Vector3::z = rhs.z;

    return *this;
}

Vector3 Vector3::operator+ (const Vector3 &rhs)
{
    return Vector3(
        Vector3::x + rhs.x,
        Vector3::y + rhs.y,
        Vector3::z + rhs.z
    );
}

Vector3 Vector3::operator+ (const double &rhs)
{
    return Vector3(
        Vector3::x + rhs,
        Vector3::y + rhs,
        Vector3::z + rhs
    );
}

Vector3 Vector3::operator+ ()
{
    return Vector3(
        Vector3::x,
        Vector3::y,
        Vector3::z
    );
}

Vector3 Vector3::operator- (const Vector3 &rhs)
{
    return Vector3(
        Vector3::x - rhs.x,
        Vector3::y - rhs.y,
        Vector3::z - rhs.z
    );
}

Vector3 Vector3::operator- (const double &rhs)
{
    return Vector3(
        Vector3::x - rhs,
        Vector3::y - rhs,
        Vector3::z - rhs
    );
}

Vector3 Vector3::operator- ()
{
    return Vector3(
        - Vector3::x,
        - Vector3::y,
        - Vector3::z
    );
}

Vector3 Vector3::operator* (const double &rhs)
{
    return Vector3(
        Vector3::x * rhs,
        Vector3::y * rhs,
        Vector3::z * rhs
    );
}

Vector3 Vector3::operator/ (const double &rhs)
{
    return Vector3(
        Vector3::x / rhs,
        Vector3::y / rhs,
        Vector3::z / rhs
    );
}

Vector3& Vector3::operator+= (const Vector3 &rhs)
{
    Vector3::x += rhs.x;
    Vector3::y += rhs.y;
    Vector3::z += rhs.z;

    return *this;
}

Vector3& Vector3::operator+= (const double &rhs)
{
    Vector3::x += rhs;
    Vector3::y += rhs;
    Vector3::z += rhs;

    return *this;
}

Vector3& Vector3::operator-= (const Vector3 &rhs)
{
    Vector3::x -= rhs.x;
    Vector3::y -= rhs.y;
    Vector3::z -= rhs.z;

    return *this;
}

Vector3& Vector3::operator-= (const double &rhs)
{
    Vector3::x -= rhs;
    Vector3::y -= rhs;
    Vector3::z -= rhs;

    return *this;
}

Vector3& Vector3::operator*= (const double &rhs)
{
    Vector3::x *= rhs;
    Vector3::y *= rhs;
    Vector3::z *= rhs;

    return *this;
}

Vector3& Vector3::operator/= (const double &rhs)
{
    Vector3::x /= rhs;
    Vector3::y /= rhs;
    Vector3::z /= rhs;

    return *this;
}

///////////////////////////////////////////////////////////////////////////

double Vector3::dot(const Vector3 &rhs)
{
	return Vector3::x*rhs.x + Vector3::y*rhs.y + Vector3::z*rhs.z;
}

Vector3 Vector3::cross(const Vector3 &rhs)
{
	return Vector3(
		Vector3::y*rhs.z - Vector3::z*rhs.y,
		-(Vector3::x*rhs.z - Vector3::z*rhs.x),
		Vector3::x*rhs.y - Vector3::y*rhs.x
	);
}

double Vector3::magnitude()
{
    // TODO: optimise this
	return sqrt(Vector3::x*Vector3::x + Vector3::y*Vector3::y + Vector3::z*Vector3::z);
}

double Vector3::magnitudeSquare()
{
	return (Vector3::x*Vector3::x + Vector3::y*Vector3::y + Vector3::z*Vector3::z);
}

void Vector3::normalise()
{
	double mag = magnitude();

	Vector3::x /= mag;
	Vector3::y /= mag;
	Vector3::z /= mag;
}