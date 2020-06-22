#pragma once
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "Texture.h"
#include <vector>

using namespace std;
using glm::vec3;

class MaterialBase
{
protected:
	ShaderProgram* program = nullptr;
public:
	MaterialBase() {}
	virtual ~MaterialBase() {
		if (program)
			delete program;
	}
	vector<Texture> textures;
	ShaderProgram& getShaderProgram() const {
		return *program;
	};
};

class PBRMaterial: public MaterialBase
{
public:
	PBRMaterial() {
		program = new ShaderProgram();
		program->CompileShader("..\\resources\\shaders\\PBRVert.glsl", OpenGLShader::VERTEX);
		program->CompileShader("..\\resources\\shaders\\PBRFrag.glsl", OpenGLShader::FRAGMENT);
		program->Link();
		program->Validate();
	};
	~PBRMaterial() {};

	vec3 albedo = vec3(1, 1, 1);
	float metallic = 0.1f;
	float roughness = 0.5f;
	float ambientOcclusion = 0.2f;
};