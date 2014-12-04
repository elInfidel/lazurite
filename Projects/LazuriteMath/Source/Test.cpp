#include "Matrix3x3.h"
#include <iostream>

using namespace lazmath;

int main()
{
	Matrix3x3 matA(19);
	Matrix3x3 matB(31);

	std::cout << matA * matB;
	system("pause");
}