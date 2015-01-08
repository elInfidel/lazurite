// ---------------------------------------------------------------------------
// Sprite.h
// A class for rendering a 2D image to the screen.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "GL/glew.h"
#include "ShaderProgram.h"
#include "Transform.h"
namespace lazurite
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();
		
		void Draw();
	
		void SetTexture(const char* a_pFilename, int& a_iWidth, int& a_iHeight, int& a_iBPP);

		Transform transform;
	
	private:
		static GLuint vao;
		static GLuint vbo;
		static GLuint ibo;
		static GLuint instances;
		GLuint textureID;

		ShaderProgram* shaderProgram;
		GLuint uniformLocation;
	
	};
}

#endif //_SPRITE_H_