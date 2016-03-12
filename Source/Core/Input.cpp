#include "Input.h"
#include <iostream>

// Static data
Input* Input::singleton;

Input::Input() : mousePosition(vec2(0, 0)), mouseDelta(vec2(0, 0)), mouseLocked(false)
{
	GLFWwindow* window = glfwGetCurrentContext();
	glfwSetKeyCallback(window, OnKey);
	glfwSetCharCallback(window, OnChar);
	glfwSetCursorPosCallback(window, OnMousePos);
	glfwSetMouseButtonCallback(window, OnMouseButton);
	glfwSetScrollCallback(window, OnMouseScroll);
}

Input::~Input()
{
	delete singleton;
}

Input* Input::GetInstance()
{
	if (singleton == nullptr)
		singleton = new Input();
	return singleton;
}

bool Input::GetKey(int key)
{
	return (keys[key] == GLFW_PRESS || keys[key] == GLFW_REPEAT);
}

bool Input::GetKeyPressed(int key)
{
	return (keys[key] == GLFW_PRESS);
}

bool Input::GetKeyDown(int key)
{
	return (keys[key] == GLFW_REPEAT);
}

bool Input::GetKeyReleased(int key)
{
	return (keys[key] == GLFW_RELEASE);
}

vec2 Input::GetMousePos()
{
	return mousePosition;
}

void Input::GetMousePos(float &x, float &y)
{
	x = mousePosition.x;
	y = mousePosition.y;
}

vec2 Input::GetMouseDelta()
{
	return mouseDelta;
}

void Input::GetMouseDelta(float &x, float &y)
{
	x = mouseDelta.x;
	y = mouseDelta.y;
}

void Input::Update(float deltaTime)
{
	// Clean up key events
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == GLFW_PRESS)
			keys[i] = GLFW_REPEAT;
		else if (keys[i] == GLFW_RELEASE)
			keys[i] = -1;
	}

	// Fix mouseDelta bug
	mouseDelta = vec2(0,0);
}

void Input::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	singleton->keys[key] = action;
}

void Input::OnChar(GLFWwindow* window, unsigned int character)
{

}

void Input::OnMousePos(GLFWwindow* window, double x, double y)
{
	singleton->mouseDelta.x = (float)x - singleton->mousePosition.x;
	singleton->mouseDelta.y = singleton->mousePosition.y - (float)y;

	singleton->mousePosition = vec2(x, y);
}

void Input::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

void Input::OnMouseScroll(GLFWwindow* window, double x, double y)
{

}
