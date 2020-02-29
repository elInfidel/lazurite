#pragma once
#include "gl_core_4_4.h"
#include "glm/glm.hpp"
#include <map>
#include <vector>
#include <string>

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

	void BindAttribLocation(GLuint loc, const char* attribName) const;
	void BindFragDataLocation(GLuint loc, const char* name)     const;

	// Set transform feedback varyings
	// NOTE: This must be called prior to linking the shader program
	void SetTransformFeedbackVaryings(unsigned int count, const char* varyings[], GLenum bufferMode);
	
	// Set uniform data in shader
	void SetUniform(const char* uniformName, const glm::vec2& data)  const;
	void SetUniform(const char* uniformName, const glm::vec3& data)  const;
	void SetUniform(const char* uniformName, const std::vector<glm::vec3> data) const;
	void SetUniform(const char* uniformName, const glm::vec4& data)  const;
	void SetUniform(const char* uniformName, const glm::mat3& data)  const;
	void SetUniform(const char* uniformName, const glm::mat4& data)  const;
	void SetUniform(const char* uniformName, const int value)   const;
	void SetUniform(const char* uniformName, const float value) const;

private:
	int handle;
	bool linked;

	typedef std::map<std::string, int> UniformMap;
	UniformMap uniformLocations;

	typedef std::map<std::string, OpenGLShader::OpenGLShaderType> ShaderMap;
	ShaderMap shaderFiles;

	//Returns the handle to a specified uniform location in the program
	int getUniformLocation(const char* uniformName) const;
};