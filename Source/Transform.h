#pragma once
#include "glm/glm.hpp"

using glm::mat4;
using glm::vec4;
using glm::vec3;

class Transform
{
public:
	Transform();
	~Transform();

	void Translate(vec3 translation);
	void Translate(float x, float y, float z);

	void Scale(vec3 scale);
	void Scale(float x, float y, float z);

	void Rotate(vec3 eular);
	void Rotate(float x, float y, float z);

	void SetPosition(vec3 newPos);
	void SetScale(vec3 newScale);
	void SetRotation(vec3 newRot);

	vec3 GetPosition();
	vec3 GetScale();
	vec3 GetRotation();

	void SetUp(vec3 newUp);
	void SetRight(vec3 newRight);
	void SetForward(vec3 newForward);

	vec3 GetUp();
	vec3 GetRight();
	vec3 GetForward();


	mat4 GetModelMatrix();

private:
	mat4 modelMatrix;
	vec3 position;
	vec3 scale;
	vec3 rotation;
	bool isDirty;
};

