// ---------------------------------------------------------------------------
// Vector3.h
// An object to represent a 3D position or direction.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#include "Vector3.h"
#include <math.h>

namespace lazmath
{
	Vector3::Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	Vector3::Vector3(float a_x, float a_y, float a_z)
	{
		x = a_x;
		y = a_y;
		z = a_z;
	}
	
	float Vector3::Magnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	
	void Vector3::Normalize()
	{
		float length = this->Magnitude();
		x /= length;
		y /= length;
		z /= length;
	}
	
	Vector3 Vector3::GetNormal()
	{
		float length = this->Magnitude();
	
		return Vector3(x /= length, y /= length, z /= length);
	}
	
	float Vector3::Dot(Vector3 lhs, Vector3 rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
	}
	
	Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
	{
		return Vector3((lhs.y * rhs.z) - (rhs.z * lhs.y), (lhs.z * rhs.x) - (lhs.x * rhs.z), (lhs.x * rhs.y) - (lhs.y * rhs.x));
	}
	
	Vector3 Vector3::operator+(Vector3 &rhs)
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	
	Vector3 Vector3::operator-(Vector3 &rhs)
	{
		return Vector3(x + -rhs.x, y + -rhs.y, z + -rhs.z);
	}
	
	Vector3 Vector3::operator*(float scalar)
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}
	
	Vector3::~Vector3()
	{
	}
}