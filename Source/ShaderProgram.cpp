#include "ShaderProgram.h"
#include "loadgen/gl_core_4_4.h"
#include "glm/gtc/type_ptr.hpp"
#include "FileIO.h"
#include <vector>
#include <iostream>

using std::vector;

namespace OpenGLShaderInfo
{
	struct shader_file_extension 
	{
		const char *ext;
		OpenGLShader::OpenGLShaderType type;
	};

	struct shader_file_extension extensions[] =
	{
		{ ".vs", OpenGLShader::VERTEX },
		{ ".vert", OpenGLShader::VERTEX },
		{ ".gs", OpenGLShader::GEOMETRY },
		{ ".geom", OpenGLShader::GEOMETRY },
		{ ".tcs", OpenGLShader::TESS_CONTROL },
		{ ".tes", OpenGLShader::TESS_EVALUATION },
		{ ".fs", OpenGLShader::FRAGMENT },
		{ ".frag", OpenGLShader::FRAGMENT },
		{ ".cs", OpenGLShader::COMPUTE }
	};
}

ShaderProgram::ShaderProgram() : handle(0), linked(false)
{
	handle = glCreateProgram();
	
	// TODO: LOG ERROR
	if (handle == 0)
		std::cout << "ERROR - Failed to create shader program!\n";
}

ShaderProgram::~ShaderProgram()
{
	if (handle == 0)
		return;

	int numShaders = 0;
	glGetProgramiv(handle, GL_ATTACHED_SHADERS, &numShaders);

	unsigned int* shaderNames = new unsigned int[numShaders];
	glGetAttachedShaders(handle, numShaders, NULL, shaderNames);

	for (int i = 0; i < numShaders; ++i)
	{
		glDeleteShader(shaderNames[i]);
	}

	glDeleteProgram(handle);
	delete[] shaderNames;
}

void ShaderProgram::CompileShader(const char* filePath, OpenGLShader::OpenGLShaderType type)
{
	string shaderCode;

	// TODO: LOG ERROR
	if (!FileIO::SyncRead(filePath, &shaderCode))
	{
		std::cout << "ERROR - Failed to load shader source code!\n";
		return;
	}

	//if (handle <= 0)
	//{
	//	handle = glCreateProgram();
	//
	//	// TODO: LOG ERROR
	//	if (handle == 0)
	//	std::cout << "ERROR - Failed to create shader program!\n";
	//}

	GLuint shaderHandle = glCreateShader(type);
	const char* cSource = shaderCode.c_str();
	glShaderSource(shaderHandle, 1, &cSource, NULL);
	glCompileShader(shaderHandle);

	// Error checking
	int compileStatus;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		int length = 0;
		string log;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, & length);
		if (length > 0)
		{
			char* rawLog = new char[length];
			int rawSize = 0;
			glGetShaderInfoLog(shaderHandle, length, &rawSize, rawLog);
			log = rawLog;
			delete[] rawLog;
		}

		string message;
		if (filePath)
		{
			message = "ERROR - " + string(filePath) + "Failed to compile! \n";
		}
		else
		{
			message = "ERROR - Failed to compile shader! \n";
		}
		message += log;

		// TODO: LOG ERROR
		std::cout << message;
	}
	else
	{
		shaderFiles.insert(std::pair<string,OpenGLShader::OpenGLShaderType>(filePath, type));
		glAttachShader(handle, shaderHandle);
	}
}

void ShaderProgram::Link()
{
	//if (linked) 
	//	return;
	//// TODO: LOG ERROR
	//if (handle <= 0)
	//	std::cout << "ERROR::SHADER::Program must be created before linking!\n";

	glLinkProgram(handle);

	// Error checking
	int linkStatus;
	glGetProgramiv(handle, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		int length = 0;
		string log;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			char* rawLog = new char[length];
			int rawSize = 0;
			glGetProgramInfoLog(handle, length, &rawSize, rawLog);
			log = rawLog;
			delete[] rawLog;
		}
		// TODO: LOG ERROR
		std::cout << "ERROR::SHADER::Failed to link program:\n" + log;
	}
	else
	{
		//uniformLocations.clear();
		linked = true;
	}

	int numShaders = 0;
	glGetProgramiv(handle, GL_ATTACHED_SHADERS, &numShaders);

	unsigned int* shaderNames = new unsigned int[numShaders];
	glGetAttachedShaders(handle, numShaders, NULL, shaderNames);

	for (int i = 0; i < numShaders; ++i)
	{
		glDetachShader(handle, shaderNames[i]);
	}

	delete[] shaderNames;
}

void ShaderProgram::Validate()
{
	//// TODO: LOG ERROR
	if (!linked)
		std::cout << "ERROR::SHADER::Program must be linked to pass validation!\n";
	
	// Error checking
	int linkStatus;
	glValidateProgram(handle);
	glGetProgramiv(handle, GL_VALIDATE_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		int length = 0;
		string log;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			char* rawLog = new char[length];
			int rawSize = 0;
			glGetProgramInfoLog(handle, length, &rawSize, rawLog);
			log = rawLog;
			delete[] rawLog;
		}
		// TODO: LOG ERROR
		std::cout << "ERROR::SHADER::Program failed validation!:\n" + log;
	}
}

void ShaderProgram::Use()
{
	// TODO: LOG ERROR
	if (handle <= 0 || (!linked))
		std::cout << "ERROR::SHADER::Shaders must be linked prior to use!\n";
	glUseProgram(handle);
}

void ShaderProgram::Reload()
{
	// TODO: Shader hot loading functionality

	typedef std::map<std::string, OpenGLShader::OpenGLShaderType>::iterator const_iter;
	for (const_iter iterator = shaderFiles.begin(); iterator != shaderFiles.end(); iterator++)
	{
		this->CompileShader(iterator->first.c_str(), iterator->second);
		std::cout << "Compiled Shader: " << iterator->first << std::endl;
	}

	this->Link();
	this->Validate();
}

int ShaderProgram::GetHandle() const
{
	if (handle == 0)
		return -1;

	return handle;
}

bool ShaderProgram::IsLinked() const
{
	return linked;
}

void ShaderProgram::BindAttribLocation(GLuint loc, const char* attribName) const
{
	glBindAttribLocation(handle, loc, attribName);
}

void ShaderProgram::BindFragDataLocation(GLuint loc, const char* name) const
{
	glBindFragDataLocation(handle, loc, name);
}

void ShaderProgram::SetTransformFeedbackVaryings(unsigned int count, const char* varyings[], GLenum bufferMode)
{
	glTransformFeedbackVaryings(handle, count, varyings, bufferMode);
}

void ShaderProgram::SetUniform(const char* uniformName, const vec2& data) const
{
	int location = getUniformLocation(uniformName);
	glUniform2fv(location, 1, glm::value_ptr(data));
}

void ShaderProgram::SetUniform(const char* uniformName, const vec3& data) const
{
	int location = getUniformLocation(uniformName);
	glUniform3fv(location, 1, glm::value_ptr(data));
}

void ShaderProgram::SetUniform(const char* uniformName, const vec4& data) const
{
	int location = getUniformLocation(uniformName);
	glUniform4fv(location, 1, glm::value_ptr(data));
}

void ShaderProgram::SetUniform(const char* uniformName, const mat3& data) const
{
	int location = getUniformLocation(uniformName);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(data));
}

void ShaderProgram::SetUniform(const char* uniformName, const mat4& data) const
{
	int location = getUniformLocation(uniformName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
}

void ShaderProgram::SetUniform(const char* uniformName, const bool value) const
{
	int location = getUniformLocation(uniformName);
	glUniform1i(location, value);
}

void ShaderProgram::SetUniform(const char* uniformName, const int value) const
{
	int location = getUniformLocation(uniformName);
	glUniform1i(location, value);
}

void ShaderProgram::SetUniform(const char* uniformName, const unsigned int value) const
{
	int location = getUniformLocation(uniformName);
	glUniform1ui(location, value);
}

void ShaderProgram::SetUniform(const char* uniformName, const float value) const
{
	int location = getUniformLocation(uniformName);
	glUniform1f(location, value);
}

void ShaderProgram::SetUniform(const char* uniformName, const double value) const
{
	int location = getUniformLocation(uniformName);
	glUniform1d(location, value);
}

int ShaderProgram::getUniformLocation(const char* uniformName) const
{
	//std::map<string, int>::iterator pos;
	//pos = uniformLocations.find(uniformName);

	//if (pos == uniformLocations.end())
	int	uniformLocation= glGetUniformLocation(handle, uniformName);

	return uniformLocation;
}