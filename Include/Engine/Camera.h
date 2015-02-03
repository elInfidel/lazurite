// ---------------------------------------------------------------------------
// Camera.h
// A class representing a camera that can be moved around the scene
//
// TODO: Everything!
//
// Original author: <Liam Parker>
// Date created: 07/01/2015
// ---------------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Transform.h"
#include "GLM/mat4x4.hpp"
#include "GLM/vec3.hpp"

using glm::mat4;
using glm::vec3;

namespace lazurite
{
	enum ProjectionType
	{
		PERSPECTIVE,
		ORTHO
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		// Returns the projection type of the camera
		ProjectionType GetType();
		// Returns the view matrix for this camera
		mat4 GetView();
		// Returns the projection matrix for this camera
		mat4 GetProjection();
		// Set the camera to orthographic mode
		void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
		// Set the camera to perspective mode
		void SetPerspective(float fov, float aspect, float zNear, float zFar);

		Transform transform;

	private:
		mat4 projection;
		ProjectionType type;

	};
}

#endif _CAMERA_H_