#pragma once
#include "loadgen/gl_core_4_4.h"
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <list>

using std::string;
using std::map;
using std::list;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

namespace OpenGLShader
{
	enum OpenGLShaderType
	{
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		TESS_CONTROL = GL_TESS_CONTROL_SHADER,
		TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
		COMPUTE = GL_COMPUTE_SHADER
	};
}

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	void CompileShader(const char* filePath, OpenGLShader::OpenGLShaderType type);

	void Link();
	void Validate();
	void Use();
	void Reload();

	int GetHandle() const;
	bool IsLinked() const;

	void BindAttribLocation(GLuint loc, const char* attribName);
	void BindFragDataLocation(GLuint loc, const char* name);

	// Set transform feedback varyings
	// NOTE: This must be called prior to linking the shader program
	void SetTransformFeedbackVaryings(unsigned int count, const char* varyings[], GLenum bufferMode);
	
	// Set uniform data in shader
	void SetUniform(const char* uniformName, const vec2& data);
	void SetUniform(const char* uniformName, const vec3& data);
	void SetUniform(const char* uniformName, const vec4& data);
	void SetUniform(const char* uniformName, const mat3& data);
	void SetUniform(const char* uniformName, const mat4& data);
	void SetUniform(const char* uniformName, const bool value);
	void SetUniform(const char* uniformName, const int value);
	void SetUniform(const char* uniformName, const unsigned int value);
	void SetUniform(const char* uniformName, const float value);
	void SetUniform(const char* uniformName, const double value);

private:
	int handle;
	bool linked;
	map<string, OpenGLShader::OpenGLShaderType> shaderFiles;
	map<string, int> uniformLocations;

	//Returns the handle to a specified uniform location in the program
	int getUniformLocation(const char* uniformName);
};

