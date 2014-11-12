// ---------------------------------------------------------------------------
// Sprite.h
// A class for rendering a 2D image to the screen.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "GL/glew.h"
#include "GL/glfw3.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Draw();
private:
	struct Vertex
	{
		// X Y Z W
		float positions[4];
		//R G B A
		float colours[4];
	};

	GLuint shaderProgram;
	//GLuint vao;
	GLuint vbo;
	GLuint ibo;
};

#endif //_SPRITE_H_