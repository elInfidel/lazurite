// ---------------------------------------------------------------------------
// ShaderProgram.h
// A class acting as a container storing multiple shaders related to an object
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_
#include "GL/glew.h"
#include "GL/glfw3.h"

namespace lazurite
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
	
		void UseProgram();
		GLuint GetProgramID();
	
		void CreateProgram(const char *a_vertex, const char *a_frag);
	
		~ShaderProgram();
	
	private:
		GLuint programID;
		static GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile);
	
	};
}

#endif // _SHADER_PROGRAM_H_