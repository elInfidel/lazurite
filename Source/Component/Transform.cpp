#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include "glm/gtx/string_cast.hpp"
#include <iostream>

Transform::Transform()
{
	isDirty = true;
	localMatrix = mat4(1);
	worldMatrix = mat4(1);

	position = vec3(0);
	rotation = quat();
	scale = vec3(1);

	bool isDirty = true;
	Transform* parent = nullptr;
}

void Transform::Translate(vec3 translation)
{
	position += translation;
	isDirty = true;
}

void Transform::Translate(float x, float y, float z)
{
	Translate(vec3(x, y, z));
}

void Transform::Rotate(vec3 eular)
{
	rotation *= quat(eular);
	isDirty = true;
}

void Transform::Rotate(float x, float y, float z)
{
	Rotate(vec3(x, y, z));
}

void Transform::Rotate(quat rotation)
{
	this->rotation *= rotation;
	isDirty = true;
}

void Transform::SetTranslation(vec3 newPos)
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
	rotation = quat(newRot);
	isDirty = true;
}

void Transform::SetRotation(quat quaternion)
{
	rotation = quaternion;
	isDirty = true;
}

vec3 Transform::GetTranslation()
{
	return position;
}

vec3 Transform::GetScale()
{
	return scale;
}

quat Transform::GetRotation()
{
	return rotation;
}

void Transform::SetRight(vec3 newRight)
{
	newRight = glm::normalize(newRight);
	localMatrix[0][0] = newRight.x;
	localMatrix[0][1] = newRight.y;
	localMatrix[0][2] = newRight.z;
}

void Transform::SetUp(vec3 newUp)
{
	newUp = glm::normalize(newUp);
	localMatrix[1][0] = newUp.x;
	localMatrix[1][1] = newUp.y;
	localMatrix[1][2] = newUp.z;
}

void Transform::SetForward(vec3 newForward)
{
	newForward = glm::normalize(newForward);
	localMatrix[2][0] = newForward.x;
	localMatrix[2][1] = newForward.y;
	localMatrix[2][2] = newForward.z;

	vec3 newRight = glm::normalize(glm::cross(this->GetForward(), vec3(0, 1, 0)));
	localMatrix[0][0] = newRight.x;
	localMatrix[0][1] = newRight.y;
	localMatrix[0][2] = newRight.z;

	vec3 newUp = glm::normalize(glm::cross(this->GetRight(), this->GetForward()));
	localMatrix[1][0] = newUp.x;
	localMatrix[1][1] = newUp.y;
	localMatrix[1][2] = newUp.z;
}

vec3 Transform::GetRight()
{
	return vec3(localMatrix[0]);
}

vec3 Transform::GetUp()
{
	return vec3(localMatrix[1]);
}

vec3 Transform::GetForward()
{
	return vec3(localMatrix[2]);
}

mat4 Transform::GetLocalMatrix()
{
	if (isDirty)
		UpdateTransformations();

	return localMatrix;
}

mat4 Transform::GetWorldMatrix()
{
	if (isDirty)
		UpdateTransformations();

	return worldMatrix;
}

void Transform::SetParent(Transform* transform)
{
	for (vector<Transform*>::iterator child = children.begin(); child != children.end(); ++child)
	{
		// You can't set a transform child as its parent!
		if ((*child) == transform)
			return;
	}

	parent = transform;
}

void Transform::AddChild(Transform* transform)
{
	for (vector<Transform*>::iterator child = children.begin(); child != children.end(); ++child)
	{
		if ((*child) == transform)
			return;
	}

	children.push_back(transform);
}

void Transform::DetachChildren()
{
	for (vector<Transform*>::iterator child = children.begin(); child != children.end(); ++child)
	{
		(*child)->parent = nullptr;
	}
	children.clear();
}

Transform* Transform::GetParent()
{
	return parent;
}

Transform* Transform::GetChildByIndex(int index)
{
	if (index < children.size())
		return children[index];
	else
		return nullptr;
}

vector<Transform*> Transform::GetChildren()
{
	return children;
}

void Transform::UpdateTransformations()
{
	localMatrix = glm::scale(scale) * glm::toMat4(rotation) * glm::translate(position);

	if (parent != nullptr)
		worldMatrix = localMatrix * parent->worldMatrix;
	else
		worldMatrix = localMatrix;

	isDirty = false;

	for (vector<Transform*>::iterator child = children.begin(); child != children.end(); ++child)
	{
		(*child)->UpdateTransformations();
	}
}

void Transform::Update(float deltaTime)
{
	if (isDirty)
		UpdateTransformations();
}
