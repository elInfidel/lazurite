#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "Component/Transform.h"

class Camera : public AComponent
{
	glm::mat4 _projection;

public:
	Camera();

	// Sets the camera to orthographic projection with the given arguments
	void SetOrthographic(float left, float right, float top, float bottom, float zNear, float zFar);
	// Sets the camera to perspective projection with the given arguments
	void SetPerspective(float fov, float aspect, float zNear = 1.0f, float zFar = 100.0f);

	// Get the current view matrix.
	const glm::mat4& GetViewMatrix();

	// Get the current projection matrix.
	const glm::mat4& GetProjectionMatrix() const;

	virtual void Tick(float deltaTime);
};