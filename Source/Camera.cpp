#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

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
	return glm::inverse(transform.GetWorldMatrix());
}

const mat4& Camera::GetProjectionMatrix() const
{
	return projection;
}
