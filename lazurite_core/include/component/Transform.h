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

	bool isDirty;

	std::shared_ptr<Transform> parent;
	std::vector<std::shared_ptr<Transform>> children;

	void UpdateTransformations();

public:
	Transform();

	void Translate(vec3 translation);
	void Rotate(vec3 eular);
	void Scale(vec3 scale);

	void SetPosition(vec3 newPos);
	void SetScale(vec3 newScale);
	void SetRotation(vec3 eular);

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

	void SetLocalMatrix(mat4 localMatrix);

	void SetParent(std::shared_ptr<Transform> transform);
	void AddChild(std::shared_ptr<Transform> transform);
	void DetachChildren();

	std::shared_ptr<Transform> GetParent();
	std::shared_ptr<Transform> GetChildByIndex(int index);
	std::vector<std::shared_ptr<Transform>> GetChildren();

	virtual void Tick(float deltaTime);
};

