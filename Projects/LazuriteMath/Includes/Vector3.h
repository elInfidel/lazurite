// ---------------------------------------------------------------------------
// Vector3.h
// An object to represent a 3D position or direction.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

namespace lazmath
{
	class Vector3
	{
	public:
		Vector3();
		Vector3(float a_x, float a_y, float a_z);
	
		float x, y, z;
			
		float Magnitude();
		void Normalize();
		Vector3 GetNormal();
	
		static float Dot(Vector3 lhs, Vector3 rhs);
		static Vector3 Cross(Vector3 lhs, Vector3 rhs);
		
		Vector3 operator+(Vector3 &rhs);
		Vector3 operator-(Vector3 &rhs);
		Vector3 operator*(float scalar);
	
		~Vector3();
	};
}

#endif // _VECTOR3_H_