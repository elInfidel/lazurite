#include "Input.h"
#include <iostream>
#include "tweakbar/AntTweakBar.h"

vec2 Input::mousePosition = vec2(0);
vec2 Input::mouseDelta = vec2(0);
map<int,int>  Input::keys = map<int, int>();
bool Input::mouseLocked = false;

void Input::Initialize()
{
	glfwSetKeyCallback(glfwGetCurrentContext(), OnKey);
	glfwSetCharCallback(glfwGetCurrentContext(), OnChar);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), OnMousePos);
	glfwSetMouseButtonCallback(glfwGetCurrentContext(), OnMouseButton);
	glfwSetScrollCallback(glfwGetCurrentContext(), OnMouseScroll);
}

void Input::ShutDown()
{

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

void Input::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	keys[key] = action;
	TwEventKeyGLFW(key, action);
}

void Input::OnChar(GLFWwindow* window, unsigned int character)
{
	TwEventCharGLFW(character, GLFW_PRESS);
}

void Input::OnMousePos(GLFWwindow* window, double x, double y)
{
	mouseDelta.x = (float)x - mousePosition.x;
	mouseDelta.y = mousePosition.y - (float)y;

	mousePosition = vec2(x,y);
	TwEventMousePosGLFW((int)x, (int)y);
}

void Input::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	TwEventMouseButtonGLFW(button, action);
}

void Input::OnMouseScroll(GLFWwindow* window, double x, double y)
{
	TwEventMouseWheelGLFW((int)y);
}
