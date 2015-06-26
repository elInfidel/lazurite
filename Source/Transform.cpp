#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <iostream>

Transform::Transform()
{
	isDirty = true;
	modelMatrix = mat4(1);
	position = vec3(0);
	rotation = vec3(0);
	scale = vec3(1);
}

Transform::~Transform()
{

}

void Transform::Translate(vec3 translation)
{
	position += translation;
	isDirty = true;
}

void Transform::Translate(float x, float y, float z)
{
	position += vec3(x, y, z);
	isDirty = true;
}

void Transform::Scale(vec3 scale)
{
	this->scale += scale;
	isDirty = true;
}

void Transform::Scale(float x, float y, float z)
{
	this->scale = vec3(x,y,z);
	isDirty = true;
}

void Transform::Rotate(vec3 eular)
{
	rotation = eular;
	isDirty = true;
}

void Transform::Rotate(float x, float y, float z)
{
	rotation = vec3(x, y, z);
	isDirty = true;
}

void Transform::SetPosition(vec3 newPos)
{
	position = newPos;
	isDirty = true;
}

void Transform::SetScale(vec3 newScale)
{
	scale = newScale;
	isDirty = true;
}

void Transform::SetRotation(vec3 newRot)
{
	rotation = newRot;
	isDirty = true;
}

vec3 Transform::GetPosition()
{
	return position;
}

vec3 Transform::GetScale()
{
	return scale;
}

vec3 Transform::GetRotation()
{
	return rotation;
}

void Transform::SetForward(vec3 newForward)
{
	newForward = glm::normalize(newForward);
	modelMatrix[2][0] = newForward.x;
	modelMatrix[2][1] = newForward.y;
	modelMatrix[2][2] = newForward.z;
}

void Transform::SetRight(vec3 newRight)
{
	newRight = glm::normalize(newRight);
	modelMatrix[0][0] = newRight.x;
	modelMatrix[0][1] = newRight.y;
	modelMatrix[0][2] = newRight.z;
}

void Transform::SetUp(vec3 newUp)
{
	newUp = glm::normalize(newUp);
	modelMatrix[1][0] = newUp.x;
	modelMatrix[1][1] = newUp.y;
	modelMatrix[1][2] = newUp.z;
}

vec3 Transform::GetRight()
{
	return vec3(modelMatrix[0]);
}

vec3 Transform::GetUp()
{
	return vec3(modelMatrix[1]);
}

vec3 Transform::GetForward()
{
	return vec3(modelMatrix[2]);
}

mat4 Transform::GetModelMatrix()
{
	if (isDirty)
	{
		mat4 rot = glm::rotate(glm::radians(rotation.z), vec3(0, 0, 1)) *
				   glm::rotate(glm::radians(rotation.y), vec3(0, 1, 0)) *
				   glm::rotate(glm::radians(rotation.x), vec3(1, 0, 0));

		modelMatrix = glm::translate(position) * rot * glm::scale(scale);

		isDirty = false;
	}

	return modelMatrix;
}