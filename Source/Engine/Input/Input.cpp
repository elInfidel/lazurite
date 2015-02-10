// ---------------------------------------------------------------------------
// Input.cpp
// Interface to input functionality
//
// Original author: <Liam Parker>
// Date created: 6/02/2015
// ---------------------------------------------------------------------------
#include "Engine/Input/Input.h"

namespace lazurite
{
	Input::Input()
	{

	}

	Input::~Input()
	{

	}

	int Input::GetKey(int key)
	{
		return glfwGetKey(glfwGetCurrentContext(), key);
	}

	vec2 Input::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
		return vec2(x, y);
	}
}