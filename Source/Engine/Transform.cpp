// ---------------------------------------------------------------------------
// Transform.cpp
// An object for storing the transformation of an object.
//
// Original author: <Liam Parker>
// Date created: 21/12/2014
// ---------------------------------------------------------------------------
#include "Engine/Transform.h"

//DEBUGGING
#include <iostream>

namespace lazurite
{
	Transform::Transform()
	{
		isDirty = false;
		position = Vector3(0.0f, 0.0f, 0.0f);
		rotation = Vector3(0.0f, 0.0f, 0.0f);
		scale = Vector3(1.0f, 1.0f, 1.0f);
		GenerateMatrix();
	}
	
	
	Transform::~Transform()
	{

	}

	void Transform::Translate(Vector3& vector)
	{
		position = vector;
		isDirty = true;
	}

	void Transform::Translate(float x, float y, float z)
	{
		position = Vector3(x, y, z);
		isDirty = true;
	}

	void Transform::Rotate(Vector3& vector)
	{
		rotation = vector;
		isDirty = true;
	}

	void Transform::Rotate(float x, float y, float z)
	{
		rotation = Vector3(x, y, z);
		isDirty = true;
	}

	void Transform::Scale(Vector3& vector)
	{
		scale = vector;
		isDirty = true;
	}

	void Transform::Scale(float x, float y, float z)
	{
		scale = Vector3(x, y, z);
		isDirty = true;
	}

	Matrix4x4 Transform::GetTransformation()
	{
		if(isDirty)
			GenerateMatrix();

		return transformation;
	}

	void Transform::GenerateMatrix()
	{
		// RST (Rotation on self origin)
		transformation = Matrix4x4::Translate(position) * Matrix4x4::Scale(scale) * Matrix4x4::Rotate(rotation.x, rotation.y, rotation.z);

		isDirty = false;
	}

}
