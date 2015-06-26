#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	transform = new Transform();
}


Camera::~Camera()
{
	delete transform;
}

void Camera::SetOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
{
	projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void Camera::SetPerspective(float fov, float aspect, float zNear, float zFar)
{
	projection = glm::perspective(fov, aspect, zNear, zFar);
}

const mat4& Camera::GetView() const
{
	return view;
}

const mat4& Camera::GetProjection() const
{
	return projection;
}

const mat4& Camera::GetProjectionView()
{
	UpdateProjectionView();
	return viewProjection;
}

void Camera::UpdateProjectionView()
{
	view = glm::lookAt(transform->GetPosition(), transform->GetPosition() + transform->GetForward(), vec3(0,1,0));
	viewProjection = projection * view;
}
