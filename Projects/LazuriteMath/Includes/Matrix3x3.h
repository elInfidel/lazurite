// ---------------------------------------------------------------------------
// Matrix3x3.h
// An object to represent a matrix 3x3
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_

#include <iostream>
#include "Vector3.h"

namespace lazmath
{
	class Matrix3x3
	{
	public:
		// Constructors

		// Initializes all components with 0.0f.
		Matrix3x3();

		// Initializes all components from the upper-left
		// to the bottom-right with the scalar argument.
		Matrix3x3(float Scalar);

		// Copy constructor creating a new matrix identical to
		// the one passed in as an argument.
		Matrix3x3(const Matrix3x3& mat);

		~Matrix3x3();
		
		// Overloads
		Matrix3x3 operator+(Matrix3x3& other);
		void operator+=(Matrix3x3& other);
	
		Matrix3x3 operator-(Matrix3x3& other);
		void operator-=(Matrix3x3& other);
	
		Matrix3x3 operator*(Matrix3x3& other);
		Vector3 operator*(Vector3& other);
		void operator*=(Matrix3x3& other);
		
		friend std::ostream& operator<<(std::ostream& os, const Matrix3x3& mat);

		// Methods

		//Transposes the matix and returns reference to it.
		Matrix3x3& Transpose();

		//Gets the transpose of the matrix without modifying it.
		Matrix3x3 GetTranspose();

		// Static Methods
		static Matrix3x3 Identity();

	private:
		float m_matrix[3][3];
	
	};
}

#endif // _MATRIX3X3_H_

