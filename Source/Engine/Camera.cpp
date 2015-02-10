// ---------------------------------------------------------------------------
// Camera.cpp
// A class representing a camera that can be moved around the scene
//
// Original author: <Liam Parker>
// Date created: 07/01/2015
// ---------------------------------------------------------------------------
#include "Engine/Camera.h"
#include "GLM/gtc/matrix_transform.hpp"

namespace lazurite
{
	Camera::Camera()
	{
		
	}
	
	Camera::~Camera()
	{
		
	}

	ProjectionType Camera::GetType()
	{
		return type;
	}

	mat4 Camera::GetView()
	{
		return transform.Inverse();
	}

	mat4& Camera::GetProjection()
	{
		return projection;
	}

	void Camera::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		type = ProjectionType::ORTHO;
		projection = glm::ortho(left, right, bottom, top, zNear, zFar);
	}

	void Camera::SetPerspective(float fov, float aspect, float zNear, float zFar)
	{
		type = ProjectionType::PERSPECTIVE;
		projection = glm::perspective(fov, aspect, zNear, zFar);
	}
}