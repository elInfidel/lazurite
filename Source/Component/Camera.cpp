#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Subsystem/Input.h"
#include "GameObject.h"

Camera::Camera()
{
	_view = mat4(1.0f);
	_projection = mat4(1.0f);
}

void Camera::SetOrthographic(float left, float right, float bottom, float top, float zNear = 1.0f, float zFar = 100.0f)
{
	_projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetPerspective(float fov, float aspect, float zNear = 1.0f, float zFar = 100.0f)
{
	_projection = glm::perspective(fov, aspect, zNear, zFar);
}

const mat4& Camera::GetViewMatrix()
{
	auto transform = gameObject.get()->GetComponent<Transform>().lock().get();
	_view = glm::inverse(transform->GetWorldMatrix());
	return _view;
}

const mat4& Camera::GetProjectionMatrix() const
{
	return _projection;
}

void Camera::Tick(float deltaTime)
{

}