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
		hasChanged = false;
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
		position += vector;
		hasChanged = true;
	}

	void Transform::Rotate(Vector3& vector)
	{
		rotation = vector;
		hasChanged = true;
	}

	void Transform::Scale(Vector3& vector)
	{
		scale = vector;
		hasChanged = true;
	}

	Matrix4x4 Transform::GetTransformation()
	{
		if(hasChanged)
			GenerateMatrix();

		return transformation;
	}

	void Transform::GenerateMatrix()
	{
		hasChanged = false;
		transformation = Matrix4x4::Translate(position) * Matrix4x4::Scale(scale) * Matrix4x4::Rotate(rotation.x, rotation.y, rotation.z);
	}

}
