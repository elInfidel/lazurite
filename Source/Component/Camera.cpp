#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Subsystem/Input.h"
#include "GameObject.h"

Camera::Camera()
{
	view = mat4(1.0f);
	projection = mat4(1.0f);
}

void Camera::SetOrthographic(float left, float right, float bottom, float top, float zNear = 1.0f, float zFar = 100.0f)
{
	projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetPerspective(float fov, float aspect, float zNear = 1.0f, float zFar = 100.0f)
{
	projection = glm::perspective(fov, aspect, zNear, zFar);
}

const mat4& Camera::GetViewMatrix()
{
	auto transform = gameObject.get()->GetComponent<Transform>().lock().get();
	return glm::inverse(transform->GetWorldMatrix());
}

const mat4& Camera::GetProjectionMatrix() const
{
	return projection;
}

void Camera::Tick(float deltaTime)
{
	CalculateMovement(deltaTime);
	CalculateRotation(deltaTime);
}

void Camera::CalculateRotation(float deltaTime)
{
	static vec2 lastOffset;
	static vec2 curOffset;
	auto transform = gameObject.get()->GetComponent<Transform>().lock().get();

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
	transform->SetForward(vec3(cos(glm::radians(pitch)) * cos(glm::radians(yaw)), sin(glm::radians(pitch)), cos(glm::radians(pitch)) * sin(glm::radians(yaw))));
	lastOffset = curOffset;
}

void Camera::CalculateMovement(float deltaTime)
{
	auto transform = gameObject.get()->GetComponent<Transform>().lock().get();
	glm::vec3 right = transform->GetRight();
	glm::vec3 up = transform->GetUp();

	// Translation
	// TODO: Wrap key enumeration in Input class instead of using GLFW directly
	float finalSpeed = deltaTime;
	if (Input::GetInstance()->GetKey(GLFW_KEY_W))
		transform->Translate(vec3(0, 0, -1) * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_S))
		transform->Translate(vec3(0, 0, 1) * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_A))
		transform->Translate(-right * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_D))
		transform->Translate(right * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_SPACE))
		transform->Translate(up * finalSpeed);
	if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT_SHIFT))
		transform->Translate(-up * finalSpeed);
}