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
	ShaderProgram* _program = nullptr;
public:
	MaterialBase() {}
	virtual ~MaterialBase() {
		if (_program)
			delete _program;
	}
	vector<Texture> textures;
	ShaderProgram& getShaderProgram() const {
		return *_program;
	};
};

class BasicMaterial : public MaterialBase
{
public:

	BasicMaterial() {
		_program = new ShaderProgram();
		_program->CompileShader("./shaders/BlinnPhongVert.glsl", OpenGLShader::VERTEX);
		_program->CompileShader("./shaders/BlinnPhongFrag.glsl", OpenGLShader::FRAGMENT);
		_program->Link();
		_program->Validate();
	};
	~BasicMaterial() {};

	vec3 ambient = vec3(1, 1, 1);
	vec3 diffuse = vec3(1, 1, 1);
	vec3 specular = vec3(1, 1, 1);
};

class PBRMaterial: public MaterialBase
{
public:
	PBRMaterial() {
		_program = new ShaderProgram();
		_program->CompileShader("./shaders/PBRVert.glsl", OpenGLShader::VERTEX);
		_program->CompileShader("./shaders/PBRFrag.glsl", OpenGLShader::FRAGMENT);
		_program->Link();
		_program->Validate();
	};
	~PBRMaterial() {};

	vec3 albedo = vec3(1, 1, 1);
	float metallic = 0.1;
	float roughness = 0.5;
	float ambientOcclusion = 0.2;
};