// ---------------------------------------------------------------------------
// Vector2.h
// An object to represent a 2D position or direction.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#include "Vector2.h"
#include <math.h>

namespace lazmath
{
	Vector2::Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2::Vector2(float a_x, float a_y)
	{
		x = a_x;
		y = a_y;
	}
	
	float Vector2::Magnitude()
	{
		return sqrtf(x * x + y * y);
	}

	void Vector2::Normalize()
	{
		float length = this->Magnitude();
		x /= length;
		y /= length;
	}

	Vector2 Vector2::GetNormal()
	{
		float length = this->Magnitude();
		
		return Vector2(x /= length, y /= length);
	}

	float Vector2::Dot(Vector2 lhs, Vector2 rhs)
	{
		return (lhs.x * rhs.x) + (lhs.y * rhs.y);
	}

	float AngleBetween(Vector2 lhs, Vector2 rhs)
	{
		//TODO
	}

	Vector2 Vector2::operator+(Vector2 &rhs)
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}
	
	Vector2 Vector2::operator-(Vector2 &rhs)
	{
		return Vector2(x + -rhs.x, y + -rhs.y);
	}
	
	Vector2 Vector2::operator*(float scalar)
	{
		return Vector2(x * scalar, y * scalar);
	}
	
	Vector2::~Vector2()
	{

	}
}