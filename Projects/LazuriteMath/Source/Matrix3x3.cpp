// ---------------------------------------------------------------------------
// Matrix3x3.cpp
// An object to represent a m_matrix 3x3
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#include "Matrix3x3.h"

using namespace::std;

namespace lazmath
{
	Matrix3x3::Matrix3x3()
	{
		for(int row = 0; row < 3; ++row)
		{
			for(int col = 0; col < 3; ++col)
			{
				m_matrix[row][col] = 0.0f;
			}
		}
	}
	
	Matrix3x3::Matrix3x3(float Scalar)
	{
		m_matrix[0][0] = Scalar;
		m_matrix[0][1] = 0.0f;
		m_matrix[0][2] = 0.0f;

		m_matrix[1][0] = 0.0f;
		m_matrix[1][1] = Scalar;
		m_matrix[1][2] = 0.0f;

		m_matrix[2][0] = 0.0f;
		m_matrix[2][1] = 0.0f;
		m_matrix[2][2] = Scalar;
	}

	Matrix3x3::Matrix3x3(const Matrix3x3& mat)
	{
		m_matrix[0][0] = mat.m_matrix[0][0];
		m_matrix[0][1] = mat.m_matrix[0][1];
		m_matrix[0][2] = mat.m_matrix[0][2];

		m_matrix[1][0] = mat.m_matrix[1][0];
		m_matrix[1][1] = mat.m_matrix[1][1];
		m_matrix[1][2] = mat.m_matrix[1][2];

		m_matrix[2][0] = mat.m_matrix[2][0];
		m_matrix[2][1] = mat.m_matrix[2][1];
		m_matrix[2][2] = mat.m_matrix[2][2];
	}
	
	Matrix3x3::~Matrix3x3()
	{

	}

	Matrix3x3 Matrix3x3::operator+(Matrix3x3 &other)
	{
		Matrix3x3 temp;

		temp.m_matrix[0][0] = m_matrix[0][0] + other.m_matrix[0][0];
		temp.m_matrix[0][1] = m_matrix[0][1] + other.m_matrix[0][1];
		temp.m_matrix[0][2] = m_matrix[0][2] + other.m_matrix[0][2];
		
		temp.m_matrix[1][0] = m_matrix[1][0] + other.m_matrix[1][0];
		temp.m_matrix[1][1] = m_matrix[1][1] + other.m_matrix[1][1];
		temp.m_matrix[1][2] = m_matrix[1][2] + other.m_matrix[1][2];
		
		temp.m_matrix[2][0] = m_matrix[2][0] + other.m_matrix[2][0];
		temp.m_matrix[2][1] = m_matrix[2][1] + other.m_matrix[2][1];
		temp.m_matrix[2][2] = m_matrix[2][2] + other.m_matrix[2][2];

		return temp;
	}

	void Matrix3x3::operator+=(Matrix3x3 &other)
	{
		m_matrix[0][0] = m_matrix[0][0] + other.m_matrix[0][0];
		m_matrix[0][1] = m_matrix[0][1] + other.m_matrix[0][1];
		m_matrix[0][2] = m_matrix[0][2] + other.m_matrix[0][2];
		
		m_matrix[1][0] = m_matrix[1][0] + other.m_matrix[1][0];
		m_matrix[1][1] = m_matrix[1][1] + other.m_matrix[1][1];
		m_matrix[1][2] = m_matrix[1][2] + other.m_matrix[1][2];
		
		m_matrix[2][0] = m_matrix[2][0] + other.m_matrix[2][0];
		m_matrix[2][1] = m_matrix[2][1] + other.m_matrix[2][1];
		m_matrix[2][2] = m_matrix[2][2] + other.m_matrix[2][2];
	}

	Matrix3x3 Matrix3x3::operator-(Matrix3x3 &other)
	{
		Matrix3x3 temp;

		temp.m_matrix[0][0] = m_matrix[0][0] - other.m_matrix[0][0];
		temp.m_matrix[0][1] = m_matrix[0][1] - other.m_matrix[0][1];
		temp.m_matrix[0][2] = m_matrix[0][2] - other.m_matrix[0][2];
		
		temp.m_matrix[1][0] = m_matrix[1][0] - other.m_matrix[1][0];
		temp.m_matrix[1][1] = m_matrix[1][1] - other.m_matrix[1][1];
		temp.m_matrix[1][2] = m_matrix[1][2] - other.m_matrix[1][2];
		
		temp.m_matrix[2][0] = m_matrix[2][0] - other.m_matrix[2][0];
		temp.m_matrix[2][1] = m_matrix[2][1] - other.m_matrix[2][1];
		temp.m_matrix[2][2] = m_matrix[2][2] - other.m_matrix[2][2];

		return temp;
	}

	void Matrix3x3::operator-=(Matrix3x3 &other)
	{
		m_matrix[0][0] = m_matrix[0][0] - other.m_matrix[0][0];
		m_matrix[0][1] = m_matrix[0][1] - other.m_matrix[0][1];
		m_matrix[0][2] = m_matrix[0][2] - other.m_matrix[0][2];
		
		m_matrix[1][0] = m_matrix[1][0] - other.m_matrix[1][0];
		m_matrix[1][1] = m_matrix[1][1] - other.m_matrix[1][1];
		m_matrix[1][2] = m_matrix[1][2] - other.m_matrix[1][2];
		
		m_matrix[2][0] = m_matrix[2][0] - other.m_matrix[2][0];
		m_matrix[2][1] = m_matrix[2][1] - other.m_matrix[2][1];
		m_matrix[2][2] = m_matrix[2][2] - other.m_matrix[2][2];
	}

	Matrix3x3 Matrix3x3::operator*(Matrix3x3 &other)
	{
		Matrix3x3 temp;

		for(int i = 0; i < 3; ++i)
		{
			temp.m_matrix[i][0] = (m_matrix[i][0] * other.m_matrix[0][0]) +
								  (m_matrix[i][1] * other.m_matrix[1][0]) +
								  (m_matrix[i][2] * other.m_matrix[2][0]);

			temp.m_matrix[i][1] = (m_matrix[i][0] * other.m_matrix[0][1]) +
								  (m_matrix[i][1] * other.m_matrix[1][1]) +
								  (m_matrix[i][2] * other.m_matrix[2][1]);

			temp.m_matrix[i][2] = (m_matrix[i][0] * other.m_matrix[0][2]) +
								  (m_matrix[i][1] * other.m_matrix[1][2]) +
								  (m_matrix[i][2] * other.m_matrix[2][2]);
		}

		return temp;
	}
	
	void Matrix3x3::operator*=(Matrix3x3 &other)
	{
		for(int i = 0; i < 3; ++i)
		{
			m_matrix[i][0] = (m_matrix[i][0] * other.m_matrix[0][0]) +
						     (m_matrix[i][1] * other.m_matrix[1][0]) +
							 (m_matrix[i][2] * other.m_matrix[2][0]);

			m_matrix[i][1] = (m_matrix[i][0] * other.m_matrix[0][1]) +
						     (m_matrix[i][1] * other.m_matrix[1][1]) +
							 (m_matrix[i][2] * other.m_matrix[2][1]);

			m_matrix[i][2] = (m_matrix[i][0] * other.m_matrix[0][2]) +
						     (m_matrix[i][1] * other.m_matrix[1][2]) +
						     (m_matrix[i][2] * other.m_matrix[2][2]);
		}
	}
	
	Vector3 Matrix3x3::operator*(Vector3& other)
	{
		return Vector3();
	}

	ostream& operator<<(ostream& os, const Matrix3x3& mat)
	{
		for(int row = 0; row < 3; ++row)
		{
			for(int col = 0; col < 3; ++col)
			{
				cout << mat.m_matrix[row][col] << " ";
			}
			cout << endl;
		}

		return os;
	}

	Matrix3x3& Matrix3x3::Transpose()
	{
		float temp;

		temp = m_matrix[0][1];
		m_matrix[0][1] = m_matrix[1][0];
		m_matrix[1][0] = temp;
		
		temp = m_matrix[0][2];
		m_matrix[0][2] = m_matrix[2][0];
		m_matrix[2][0] = temp;
		
		temp = m_matrix[1][2];
		m_matrix[1][2] = m_matrix[2][1];
		m_matrix[2][1] = temp;

		return *this;
	}

	Matrix3x3 Matrix3x3::Identity()
	{
		return Matrix3x3(1.0f);
	}

	Matrix3x3 Matrix3x3::GetTranspose()
	{
		Matrix3x3 temp;

		temp.m_matrix[0][0] = m_matrix[0][0];
		temp.m_matrix[0][1] = m_matrix[1][0];
		temp.m_matrix[1][0] = m_matrix[0][1];

		temp.m_matrix[1][1] = m_matrix[1][1];
		temp.m_matrix[0][2] = m_matrix[2][0];
		temp.m_matrix[2][0] = m_matrix[0][2];

		temp.m_matrix[2][2] = m_matrix[2][2];
		temp.m_matrix[1][2] = m_matrix[2][1];
		temp.m_matrix[2][1] = m_matrix[1][2];

		return temp;
	}

}
