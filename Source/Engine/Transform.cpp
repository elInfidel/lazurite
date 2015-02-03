// ---------------------------------------------------------------------------
// Transform.cpp
// An object for storing the transformation of an object.
//
// Original author: <Liam Parker>
// Date created: 21/12/2014
// ---------------------------------------------------------------------------
#include "Engine/Transform.h"
#include "GLM/gtc/matrix_transform.hpp"

namespace lazurite
{
	Transform::Transform()
	{
		isDirty = false;
		translation = vec3(0.0f, 0.0f, 0.0f);
		rotation = vec3(0.0f, 0.0f, 0.0f);
		scale = vec3(10.0f, 10.0f, 10.0f);
		GenerateMatrix();
	}
	
	Transform::~Transform()
	{

	}

	void Transform::Translate(vec3& vector)
	{
		translation += vector;
		isDirty = true;
	}

	void Transform::Translate(float x, float y, float z)
	{
		translation += vec3(x, y, z);
		isDirty = true;
	}

	void Transform::Rotate(vec3& vector)
	{
		rotation = vector;
		isDirty = true;
	}

	void Transform::Rotate(float x, float y, float z)
	{
		rotation = vec3(x, y, z);
		isDirty = true;
	}

	void Transform::Scale(vec3& vector)
	{
		scale = vector;
		isDirty = true;
	}

	void Transform::Scale(float x, float y, float z)
	{
		scale = vec3(x, y, z);
		isDirty = true;
	}

	mat4 Transform::GetTransformation()
	{
		if(isDirty)
			GenerateMatrix();

		return transformation;
	}

	mat4 Transform::Inverse()
	{
		if (isDirty)
			GenerateMatrix();

		return glm::inverse(transformation);
	}

	void Transform::GenerateMatrix()
	{
		// RST (Rotation on self origin)
		transformation = glm::translate(mat4(1.0f), translation) * glm::scale(mat4(1.0f), scale) * glm::rotate(mat4(1.0f), rotation.z, vec3(0, 0, 1));

		isDirty = false;
	}

}
