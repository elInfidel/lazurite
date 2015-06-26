#pragma once
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "Transform.h"

using glm::mat4;
using glm::vec3;

class Camera
{
public:
	Camera();
	virtual ~Camera();

	// Sets the camera to orthographic with the given arguments
	void SetOrthographic(float left, float right, float top, float bottom, float zNear, float zFar);
	// Sets the camera to perspective with the given arguments
	void SetPerspective(float fov, float aspect, float zNear, float zFar);

	const mat4& GetView()       const;
	const mat4& GetProjection() const;
	const mat4& GetProjectionView();

	// Called once per update passing accessing to current deltaTime
	virtual void Update(float deltaTime) = 0;

private:
	// Camera view projection data
	mat4 view;
	mat4 projection;
	mat4 viewProjection;

	// Regenerates the current ProjectionView
	void UpdateProjectionView();

public:
	Transform* transform;
};

