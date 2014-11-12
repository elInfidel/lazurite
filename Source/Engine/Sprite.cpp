// ---------------------------------------------------------------------------
// Sprite.cpp
// A class for rendering a 2D image to the screen.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------

#include "Engine/Sprite.h"
#include <iostream>

Sprite::Sprite()
{
	//Creating a quad
	Vertex* quad = new Vertex[4];

	//Setting each verts X & Y coord
	quad[0].positions[0] = -0.5f;
	quad[0].positions[1] = -0.5f;
	quad[1].positions[0] = -0.5f;
	quad[1].positions[1] = 0.5f;
	quad[2].positions[0] = 0.5f;
	quad[2].positions[1] = 0.5f;
	quad[3].positions[0] = 0.5f;
	quad[3].positions[1] = -0.5f;

	for(int i =0; i < 4; ++i)
	{
		//Setting each verts Y position to 0 and clip value to 1
		quad[i].positions[2] = 0.0f;
		quad[i].positions[3] = 1.0f;

		//Setting colour to flat white with no transparency
		quad[i].colours[0] = 1.0f;
		quad[i].colours[1] = 1.0f;
		quad[i].colours[2] = 1.0f;
		quad[i].colours[3] = 1.0f;
	}

	//Create IDs for VBO & IBO
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	if(vbo != 0)
	{
		//Bind the VBO
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//Allocate space for verts on GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, quad, GL_STATIC_DRAW);
		//Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if(ibo != 0)
	{
		//Creating index array order
		char indices[4] = {0, 1, 2, 3};
		//Bind the IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//Allocate space for index data on GPU
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(char)*4, indices, GL_STATIC_DRAW);
		//Unbind the buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	//Delete vertex data on RAM now it has been moved to GPU
	delete[4] quad;
}

void Sprite::Draw()
{
	//Use shader program
	glUseProgram(shaderProgram);

	//Bind the vbo & ibo
	glBindBuffer(GL_VERTEX_ARRAY, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	//Enable vertex array states for shader (AttribArray and AttribPointer)
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));

	//Draw elements
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, NULL);

	//Unbind buffers
	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

Sprite::~Sprite()
{
	//deleting the IBO data
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}
