#pragma once
#include "glfw/glfw3.h"

class Window
{
public:
	Window();
	virtual ~Window();

	GLFWwindow* GetHandle();

private:
	GLFWwindow* windowPtr;

	int width;
	int height;

	void OnFrameBufferResize();
};

