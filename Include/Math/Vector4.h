// ---------------------------------------------------------------------------
// Vector4.h
// An object to represent a 4 dimensional data structure
//
// Original author: <Liam Parker>
// Date Created: 10/12/2014
// ---------------------------------------------------------------------------
#ifndef _VECTOR4_H_
#define _VECTOR4_H_

namespace lazmath
{
	class Vector4
	{
	public:
		// Constructs a matrix with X,Y,Z set to 0.0f and W set to 1.0f
		Vector4();
		~Vector4();
		// Constructs a vector4 with the components passed in
		Vector4(float a_x, float a_y, float a_z, float a_w);
		// Copy constructor
		Vector4(const Vector4& other);

		// Vector components
		float x, y, z, w;
	};
}

#endif //_VECTOR4_H_
