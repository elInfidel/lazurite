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

namespace lazurite
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();
	
		void Draw();
	
		//Temporary functions
		void loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP);
	
	private:
		struct Vertex
		{
			// X Y Z W
			float positions[4];
			// R G B A
			float colours[4];
			// U V
			float uv[2];
		};
	
		ShaderProgram *shaderProgram;
		GLuint vbo;
		GLuint textureID;
	
	};
}

#endif //_SPRITE_H_