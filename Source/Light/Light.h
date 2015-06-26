#pragma once
#define GLM_FORCE_PURE
#include "../Transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

using glm::vec3;

class Light
{
public:
	Light();
	~Light();

	vec3 GetLightColor();

	void SetLightColor(vec3 newColor);

private:
	float intensity;
	vec3 lightColor;
	Transform* transform;
};

