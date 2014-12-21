// ---------------------------------------------------------------------------
// Matrix4x4.h
// An object to represent a matrix 4x4
//
// Original author: <Liam Parker>
// Date Created: 2/12/2014
// ---------------------------------------------------------------------------
#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include <iostream>
#include "Vector4.h"
#include "Vector3.h"
#include "Matrix3x3.h"

namespace lazmath
{
	class Matrix4x4
	{
	public:
		// Constructs a matrix with all components set to 0.0f
		Matrix4x4();
		~Matrix4x4();
		// Constructs a diagonal matrix based off a scalar input
		Matrix4x4(float scalar);
		// Constructs a matrix4x4 with data from a matrix3x3 filling the top left 3x3 area
		Matrix4x4(const Matrix3x3& mat);
		// Copy constructor creating a new matrix identical to
		// the one passed in as an argument.
		Matrix4x4(const Matrix4x4& mat);
	
		// Returns a new identity matrix
		static const Matrix4x4 Identity;
		// Returns a new rotation matrix from a vector
		static Matrix4x4 Rotate(Vector3 rotate);
		// Returns a new rotation matrix from 3 floats
		static Matrix4x4 Rotate(float x, float y, float z);
		// Returns a new scale matrix built from a Vector2
		static Matrix4x4 Scale(Vector3 scale);
		// Returns a new scale matrix built from a uniform scalar
		static Matrix4x4 Scale(float uniformScale);
		// Returns a new translation matrix built from a Vector3
		static Matrix4x4 Translate(Vector3 translation);
		// Returns a new translation matrix built from floats
		static Matrix4x4 Translate(float x, float y, float z);
		// Returns an orthographic projection matrix
		static Matrix4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
		// Returns a perspective projection matrix
		static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);

		// Transposes the matrix and returns a pointer to it
		Matrix4x4& Transpose();
		// Builds and returns a matrix that is the transpose of the argument
		Matrix4x4 GetTranspose();
	
		// Overloads
		Matrix4x4 operator+(Matrix4x4& other);
		void operator+=(Matrix4x4& other);
		
		Matrix4x4 operator-(Matrix4x4& other);
		void operator-=(Matrix4x4& other);
		
		Matrix4x4 operator*(Matrix4x4& other);
		Vector4 operator*(Vector4& other);
		void operator*=(Matrix4x4& other);
		
		friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat);

		// Matrix components
		float m_matrix[4][4];
	};
}

#endif // _MATRIX4X4_H_