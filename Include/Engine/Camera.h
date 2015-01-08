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
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"

namespace lazurite
{
	enum Projection
	{
		PERSPECTIVE,
		ORTHO
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		Projection GetType();
		Matrix4x4 GetProjection();
		Matrix4x4 GetView();
		void SetOrtho();
		void SetPerspective();


		Transform transform;

	private:
		Projection projection;

	};
}

#endif _CAMERA_H_