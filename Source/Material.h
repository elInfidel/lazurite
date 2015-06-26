#pragma once
#include "glm/glm.hpp"

using glm::vec3;

class Material
{
public:
	Material();
	virtual ~Material();

	struct MaterialProperties
	{
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
		float shininess;
	} properties;

};

