#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "Component/Transform.h"

using glm::mat4;
using glm::vec3;

class Camera : public AComponent
{
private:
	// Camera view projection data
	mat4 _view;
	mat4 _projection;

public:
	Camera();

	// Sets the camera to orthographic projection with the given arguments
	void SetOrthographic(float left, float right, float top, float bottom, float zNear, float zFar);
	// Sets the camera to perspective projection with the given arguments
	void SetPerspective(float fov, float aspect, float zNear, float zFar);

	const mat4& GetViewMatrix();
	const mat4& GetProjectionMatrix() const;

	// Called once per update passing accessing to current deltaTime
	virtual void Tick(float deltaTime);
};