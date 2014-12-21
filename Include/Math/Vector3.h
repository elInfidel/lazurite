// ---------------------------------------------------------------------------
// Vector3.h
// An object to represent a 3D position or direction.
//
// Original author: <Liam Parker>
// Date Created: 11/11/2014
// ---------------------------------------------------------------------------
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

namespace lazmath
{
	class Vector3
	{
	public:
		// Constructor setting all components to 0.0f
		Vector3();
		~Vector3();
		// Constructor taking in 3 floats to initialize components
		Vector3(float a_x, float a_y, float a_z);
		// Copy Constructor
		Vector3(const Vector3& other);
		
		// Returns the length of the vector
		float Magnitude();
		// Sets the vectors length to 1.0f
		void Normalize();
		// Returns a copy of the vector with the length set to 1.0f
		Vector3 GetNormal();
		
		// Returns the dot product of the two vectors
		static float Dot(Vector3 lhs, Vector3 rhs);
		// Returns the cross product of the two vectors
		static Vector3 Cross(Vector3 lhs, Vector3 rhs);
		
		// Operator overloads
		Vector3 operator+(Vector3& rhs);
		void operator+=(Vector3& rhs);
		Vector3 operator-(Vector3& rhs);
		void operator-=(Vector3& rhs);
		Vector3 operator*(float scalar);

		// Vector components
		float x, y, z;
	};
}

#endif // _VECTOR3_H_