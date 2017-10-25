/*#pragma once
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "Texture.h"
#include <vector>

using namespace std;
using glm::vec3;

class Material
{
private:
	ShaderProgram* _program;
public:
	Material();
	Material(ShaderProgram* shaderProgram);
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

	ShaderProgram& getShaderProgram() const;
	void setShaderProgram(ShaderProgram* shaderProgram);
};

*/