#pragma once
#include "glm/glm.hpp"
#include "Texture.h"
#include <vector>

using namespace std;
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
		float roughness;
		float fresnel;
	} properties;

	vector<Texture> textures;

};

