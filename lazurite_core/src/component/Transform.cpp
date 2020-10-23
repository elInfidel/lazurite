#include "component/Transform.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <iostream>

Transform::Transform()
{
	parent = nullptr;

	isDirty = true;

	localMatrix = mat4(1);
	worldMatrix = mat4(1);

	bool isDirty = true;
	Transform* parent = nullptr;
}

void Transform::Translate(vec3 translation)
{
	this->localMatrix = glm::translate(this->localMatrix, translation);
	isDirty = true;
}

void Transform::Rotate(vec3 eular)
{
}


void Transform::Scale(vec3 scale)
{
	this->localMatrix = glm::scale(this->localMatrix, scale);
	isDirty = true;
}

void Transform::SetPosition(vec3 position)
{
	this->localMatrix[3] = vec4(position, 1);
	isDirty = true;
}

void Transform::SetScale(vec3 scale)
{
	this->localMatrix = glm::scale(this->localMatrix, scale);
	isDirty = true;
}

void Transform::SetRotation(vec3 rotation)
{
	this->localMatrix = this->localMatrix * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
	isDirty = true;
}

vec3 Transform::GetPosition() const
{
	return localMatrix[3];
}

vec3 Transform::GetScale() const
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(this->localMatrix, scale, rotation, translation, skew, perspective);
	return scale;
}

quat Transform::GetRotation() const
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(this->localMatrix, scale, rotation, translation, skew, perspective);
	return glm::conjugate(rotation);
}

void Transform::SetRight(vec3 newRight)
{
	newRight = glm::normalize(newRight);
	localMatrix[0][0] = newRight.x;
	localMatrix[0][1] = newRight.y;
	localMatrix[0][2] = newRight.z;
	isDirty = true;
}

void Transform::SetUp(vec3 newUp)
{
	newUp = glm::normalize(newUp);
	localMatrix[1][0] = newUp.x;
	localMatrix[1][1] = newUp.y;
	localMatrix[1][2] = newUp.z;
	isDirty = true;
}

void Transform::SetForward(vec3 newForward)
{
	newForward = glm::normalize(newForward);
	localMatrix[2][0] = newForward.x;
	localMatrix[2][1] = newForward.y;
	localMatrix[2][2] = newForward.z;

	vec3 newRight = glm::normalize(glm::cross(newForward, vec3(0, 1, 0)));
	localMatrix[0][0] = newRight.x;
	localMatrix[0][1] = newRight.y;
	localMatrix[0][2] = newRight.z;

	vec3 newUp = glm::normalize(glm::cross(this->GetRight(), newForward));
	localMatrix[1][0] = newUp.x;
	localMatrix[1][1] = newUp.y;
	localMatrix[1][2] = newUp.z;

	isDirty = true;
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

mat4& Transform::GetLocalMatrix()
{
	if (isDirty)
		UpdateTransformations();

	return localMatrix;
}

mat4& Transform::GetWorldMatrix()
{
	if (isDirty)
		UpdateTransformations();

	return worldMatrix;
}

void Transform::SetLocalMatrix(mat4 localMatrix)
{
	this->localMatrix = localMatrix;
	isDirty = true;
}

void Transform::SetParent(std::shared_ptr<Transform> transform)
{
	for (auto child = children.begin(); child != children.end(); ++child)
	{
		// You can't set a transform child as its parent!
		if ((*child) == transform)
			return;
	}

	parent = transform;
	isDirty = true;
}

void Transform::AddChild(std::shared_ptr<Transform> transform)
{
	for (auto child = children.begin(); child != children.end(); ++child)
	{
		if ((*child) == transform)
			return;
	}

	children.push_back(transform);
}

void Transform::DetachChildren()
{
	for (auto child = children.begin(); child != children.end(); ++child)
	{
		(*child)->parent = nullptr;
	}
	children.clear();
}

std::shared_ptr<Transform> Transform::GetParent()
{
	return parent;
}

std::shared_ptr<Transform> Transform::GetChildByIndex(int index)
{
	if ((size_t)index < children.size())
		return children[index];
	else
		return nullptr;
}

std::vector<std::shared_ptr<Transform>> Transform::GetChildren()
{
	return children;
}

void Transform::UpdateTransformations()
{
	if (parent != nullptr)
		worldMatrix = localMatrix * parent->worldMatrix;
	else
		worldMatrix = localMatrix;

	isDirty = false;

	for (auto child = children.begin(); child != children.end(); ++child)
	{
		(*child)->UpdateTransformations();
	}
}

void Transform::Tick(float deltaTime)
{
	if (isDirty)
		UpdateTransformations();
}
