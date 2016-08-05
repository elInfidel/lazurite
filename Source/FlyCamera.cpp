#define GLM_SWIZZLE
#include "FlyCamera.h"
#include <glm/ext.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Input.h"
#include <iostream>

FlyCamera::FlyCamera() : yaw(-90.0f), pitch(0.0f) {}
FlyCamera::~FlyCamera() {}

void FlyCamera::Update(float deltaTime)
{
	CalculateMovement(deltaTime);
	CalculateRotation(deltaTime);
}

void FlyCamera::CalculateRotation(float deltaTime)
{
	//static vec2 lastOffset;
	//static vec2 curOffset;
	//
	//curOffset = Input::GetInstance()->GetMouseDelta();
	//
	//if (curOffset == lastOffset)
	//{
	//	yaw += 0.0f;
	//	pitch += 0.0f;
	//}
	//else
	//{
	//	yaw += curOffset.x * sensitivity;
	//	pitch += curOffset.y * sensitivity;
	//}
	//
	//if (pitch > 89.0f)
	//	pitch = 89.0f;
	//if (pitch < -89.0f)
	//	pitch = -89.0f;
	//
	//// We also recalculate our direction vectors // TODO: Move this to transform class?
	//transform.SetForward(vec3(cos(glm::radians(pitch)) * cos(glm::radians(yaw)), sin(glm::radians(pitch)), cos(glm::radians(pitch)) * sin(glm::radians(yaw))));
	//
	//lastOffset = curOffset;

	// check for rotation
	static GLFWwindow* window = glfwGetCurrentContext();
	static bool sbMouseButtonDown = false;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		static double siPrevMouseX = 0;
		static double siPrevMouseY = 0;

		if (sbMouseButtonDown == false)
		{
			sbMouseButtonDown = true;
			glfwGetCursorPos(window, &siPrevMouseX, &siPrevMouseY);
		}

		double mouseX = 0, mouseY = 0;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		double iDeltaX = mouseX - siPrevMouseX;
		double iDeltaY = mouseY - siPrevMouseY;

		siPrevMouseX = mouseX;
		siPrevMouseY = mouseY;

		glm::mat4 mMat;

		// pitch
		mat4 m_transform = transform.GetWorldMatrix();
		if (iDeltaY != 0)
		{
			mMat = glm::axisAngleMatrix(transform.GetWorldMatrix()[0].xyz(), (float)-iDeltaY / 150.0f);
			m_transform[0] = mMat * m_transform[0];
			m_transform[1] = mMat * m_transform[1];
			m_transform[2] = mMat * m_transform[2];
		}

		// yaw
		if (iDeltaX != 0)
		{
			mMat = glm::axisAngleMatrix(transform.GetUp(), (float)-iDeltaX / 150.0f);
			m_transform[0] = mMat * m_transform[0];
			m_transform[1] = mMat * m_transform[1];
			m_transform[2] = mMat * m_transform[2];
		}
	}
	else
	{
		sbMouseButtonDown = false;
	}
}

void FlyCamera::CalculateMovement(float deltaTime)
{
	// Translation
	// TODO: Wrap key enumeration in Input class instead of using GLFW directly
	float finalSpeed = deltaTime;
	if (Input::GetInstance()->GetKey(GLFW_KEY_W))
		transform.Translate(vec3(0,0,-1) * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_S))
		transform.Translate(vec3(0, 0, 1) * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_A))
		transform.Translate(-transform.GetRight() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_D))
		transform.Translate(transform.GetRight() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_SPACE))
		transform.Translate(transform.GetUp() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT_SHIFT))
		transform.Translate(-transform.GetUp() * finalSpeed);
}