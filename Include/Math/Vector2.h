// ---------------------------------------------------------------------------
// Vector2.h
// An object to represent a 2D position or direction.
//
// Original author: <Liam Parker>
// Date Created: 11/11/2014
// ---------------------------------------------------------------------------
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace lazmath
{
	class Vector2
	{
	public:
		// Constructor setting all components to 0.0f
		Vector2();
		~Vector2();
		// Constructor taking in 2 floats to initialize components
		Vector2(float a_x, float a_y);
		// Copy constructor
		Vector2(const Vector2& other);
		
		// Returns the length of the vector
		float Magnitude();
		// Sets the vectors length to 1.0f
		void Normalize();
		// Returns a copy of the vector with the length set to 1.0f
		Vector2 GetNormal();

		// Returns the dot product of the two vectors
		static float Dot(Vector2 lhs, Vector2 rhs);
		
		// Operator overloads
		Vector2 operator+(Vector2 &rhs);
		Vector2 operator-(Vector2 &rhs);
		Vector2 operator*(float scalar);

		float x, y;
	};
}

#endif // _VECTOR2_H_