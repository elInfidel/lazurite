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
	static vec2 lastOffset;
	static vec2 curOffset;
	
	curOffset = Input::GetInstance()->GetMouseDelta();

	if (curOffset != lastOffset)
	{
		yaw += curOffset.x * sensitivity;
		pitch += curOffset.y * sensitivity;
	}
	else
	{
		yaw = pitch = 0.0f;
	}

	glm::clamp(pitch, -89.0f, 89.0f);

	// We also recalculate our direction vectors // TODO: Move this to transform class?
	transform.SetForward(vec3(cos(glm::radians(pitch)) * cos(glm::radians(yaw)), sin(glm::radians(pitch)), cos(glm::radians(pitch)) * sin(glm::radians(yaw))));

	lastOffset = curOffset;
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