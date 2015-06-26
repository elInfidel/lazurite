#pragma once
#include "Light.h"

class DirectionalLight : Light
{
public:
	DirectionalLight();
	~DirectionalLight();

	vec3 GetDirection();
};

