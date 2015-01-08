// ---------------------------------------------------------------------------
// Matrix3x3.h
// An object to represent a matrix 3x3
//
// Original author: <Liam Parker>
// Date Created: 2/12/2014
// ---------------------------------------------------------------------------
#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include <iostream>
#include "Vector3.h"
#include "Vector2.h"

namespace lazmath
{
	class Matrix3x3
	{
	public:
		// Constructs a matrix with all components set to 0.0f
		Matrix3x3();
		~Matrix3x3();
		// Constructs a diagonal matrix based off a scalar input
		Matrix3x3(float scalar);
		// Copy constructor
		Matrix3x3(const Matrix3x3& mat);

		// Returns a new identity matrix
		static const Matrix3x3 Identity;
		// Returns a new rotation matrix
		static Matrix3x3 Rotate(float radians);
		// Returns a new scale matrix built from a Vector2
		static Matrix3x3 Scale(Vector2 scale);
		// Returns a new scale matrix built from floats
		static Matrix3x3 Scale(float x, float y);
		// Returns a new translation matrix built from a Vector2
		static Matrix3x3 Translate(Vector2 translation);
		// Returns a new translation matrix built from floats
		static Matrix3x3 Translate(float x, float y);

		// Transposes the matrix and returns a pointer to it
		Matrix3x3& Transpose();
		// Builds and returns a matrix that is the transpose of the argument
		Matrix3x3 GetTranspose();

		// Overloads
		Matrix3x3 operator+(Matrix3x3& other);
		void operator+=(Matrix3x3& other);
	
		Matrix3x3 operator-(Matrix3x3& other);
		void operator-=(Matrix3x3& other);
	
		Matrix3x3 operator*(Matrix3x3& other);
		Vector3 operator*(Vector3& other);
		void operator*=(Matrix3x3& other);
		
		friend std::ostream& operator<<(std::ostream& os, const Matrix3x3& mat);

		// Matrix components
		float m_matrix[3][3];
	
	};
}

#endif // _MATRIX3X3_H_

