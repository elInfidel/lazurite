#include "FlyCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Input.h"
#include <iostream>

FlyCamera::FlyCamera() : yaw(-90.0f), pitch(0.0f)
{

}

FlyCamera::~FlyCamera()
{

}

void FlyCamera::Update(float deltaTime)
{
	CalculateMovement(deltaTime);

	if (!Input::GetInstance()->mouseLocked)
		return;

	CalculateRotation(deltaTime);
}

void FlyCamera::CalculateRotation(float deltaTime)
{
	static vec2 lastOffset;
	if (Input::GetInstance()->GetMouseDelta() == lastOffset)
	{
		yaw += 0.0f;
		pitch += 0.0f;
	}
	else
	{
		yaw += Input::GetInstance()->GetMouseDelta().x * sensitivity;
		pitch += Input::GetInstance()->GetMouseDelta().y * sensitivity;
	}

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// We also recalculate our direction vectors // TODO: Move this to transform class?
	transform->SetForward(vec3(cos(glm::radians(pitch)) * cos(glm::radians(yaw)), sin(glm::radians(pitch)), cos(glm::radians(pitch)) * sin(glm::radians(yaw))));

	transform->SetRight(glm::normalize(glm::cross(transform->GetForward(), vec3(0, 1, 0)))); // Temp - world up
	transform->SetUp(glm::normalize(glm::cross(transform->GetRight(), transform->GetForward())));

	lastOffset = Input::GetInstance()->GetMouseDelta();
}

void FlyCamera::CalculateMovement(float deltaTime)
{
	// Translation
	// TODO: Wrap key enumeration in Input class instead of using GLFW directly
	float finalSpeed = movementSpeed * deltaTime;
	if (Input::GetInstance()->GetKey(GLFW_KEY_W))
		transform->Translate(transform->GetForward() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_S))
		transform->Translate(-transform->GetForward() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_A))
		transform->Translate(-transform->GetRight() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_D))
		transform->Translate(transform->GetRight() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_SPACE))
		transform->Translate(transform->GetUp() * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT_SHIFT))
		transform->Translate(-transform->GetUp() * finalSpeed);
}