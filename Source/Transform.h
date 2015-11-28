#pragma once
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtx/quaternion.hpp>

using namespace std;

using glm::quat;
using glm::mat4;
using glm::vec4;
using glm::vec3;

class Transform
{
public:
	Transform();

	void Translate(vec3 translation);
	void Translate(float x, float y, float z);

	void Rotate(vec3 eular);
	void Rotate(float x, float y, float z);
	void Rotate(quat rotation);

	void SetTranslation(vec3 newPos);
	void SetScale(vec3 newScale);
	void SetRotation(vec3 eular);
	void SetRotation(quat quaternion);

	vec3 GetTranslation();
	vec3 GetScale();
	quat GetRotation();

	void SetRight(vec3 newRight);
	void SetUp(vec3 newUp);
	void SetForward(vec3 newForward);

	vec3 Transform::GetRight();
	vec3 Transform::GetUp();
	vec3 Transform::GetForward();

	mat4 GetLocalMatrix();
	mat4 GetWorldMatrix();

	void SetParent(Transform* transform);
	void AddChild(Transform* transform);
	void DetachChildren();

	Transform* GetParent();
	Transform* GetChildByIndex(int index);
	vector<Transform*> GetChildren();

private:
	mat4 localMatrix;
	mat4 worldMatrix;

	vec3 position;
	vec3 scale;
	quat rotation;
	bool isDirty;

	Transform* parent;
	vector<Transform*> children;

	void UpdateTransformations();
};

