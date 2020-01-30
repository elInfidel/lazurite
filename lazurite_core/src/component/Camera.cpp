#include "component/Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Subsystem/Input.h"
#include "GameObject.h"

Camera::Camera()
{
	this->SetPerspective(70.0f, 1920.0f/1080.0f);
}

void Camera::SetOrthographic(float left, float right, float bottom, float top, float zNear = 1.0f, float zFar = 100.0f)
{
	_projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetPerspective(float fov, float aspect, float zNear, float zFar)
{
	_projection = glm::perspective(fov, aspect, zNear, zFar);
}

const glm::mat4& Camera::GetViewMatrix()
{
	auto worldMat = gameObject->GetComponent<Transform>().lock()->GetWorldMatrix();
	return glm::inverse(worldMat);
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
	return _projection;
}

void Camera::Tick(float deltaTime)
{

}