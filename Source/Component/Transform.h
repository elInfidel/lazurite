#pragma once
#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "AComponent.h"
#include <vector>
#include <memory>

using glm::quat;
using glm::mat4;
using glm::vec4;
using glm::vec3;

class Transform : public AComponent
{
	mat4 localMatrix;
	mat4 worldMatrix;

	vec3 position;
	vec3 scale;
	quat rotation;
	bool isDirty;

	Transform* parent;
	std::vector<Transform*> children;

	void UpdateTransformations();

public:
	Transform();

	void Translate(vec3 translation);
	void Translate(float x, float y, float z);

	void Rotate(vec3 eular);
	void Rotate(float x, float y, float z);
	void Rotate(quat rotation);

	void SetPosition(vec3 newPos);
	void SetScale(vec3 newScale);
	void SetRotation(vec3 eular);
	void SetRotation(quat quaternion);

	vec3 GetPosition() const;
	vec3 GetScale() const;
	quat GetRotation() const;

	void SetRight(vec3 newRight);
	void SetUp(vec3 newUp);
	void SetForward(vec3 newForward);

	vec3 GetRight();
	vec3 GetUp();
	vec3 GetForward();

	mat4& GetLocalMatrix();
	mat4& GetWorldMatrix();

	void SetParent(Transform* transform);
	void AddChild(Transform* transform);
	void DetachChildren();

	Transform* GetParent();
	Transform* GetChildByIndex(int index);
	std::vector<Transform *> GetChildren();

	virtual void Tick(float deltaTime);
};

