// ---------------------------------------------------------------------------
// Vector2.h
// An object to represent a 2D position or direction.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

namespace lazmath
{
	class Vector2
	{
	public:
		Vector2();
		Vector2(float a_x, float a_y);
	
		float x, y;
		
		float Magnitude();
		void Normalize();
		Vector2 GetNormal();

		static float Dot(Vector2 lhs, Vector2 rhs);
		static float Cross(Vector2 lhs, Vector2 rhs);
		
		Vector2 operator+(Vector2 &rhs);
		Vector2 operator-(Vector2 &rhs);
		Vector2 operator*(float scalar);
	
		~Vector2();
	};
}

#endif // _VECTOR2_H_