// ---------------------------------------------------------------------------
// Input.h
// Interface to input functionality
//
// Original author: <Liam Parker>
// Date created: 6/02/2015
// ---------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_
#include "GL/glew.h"
#include "GL/glfw3.h"
#include "GLM/vec2.hpp"

using glm::vec2;

namespace lazurite
{
	class Input
	{
	public:
		static int GetKey(int key);
		static vec2 GetMousePos();
	private:
		Input();
		~Input();
		static Input input;
	};
}

#endif // _INPUT_H_