// ---------------------------------------------------------------------------
// Sprite.cpp
// A class for rendering a 2D image to the screen.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------

#include "Engine/Sprite.h"
#include <iostream>
#include "Engine/ShaderProgram.h"
#include "GL/glfw3.h"
//Includes below this line are temporary
//to support texturing until a class is developed to contain them
#include "SOIL/SOIL.h"

namespace lazurite
{
	Sprite::Sprite()
	{
		//Creating a shader program
		shaderProgram = new ShaderProgram();

		//Creating a quad
		Vertex* quad = new Vertex[4];
	
		//Setting verts X Y coords
		quad[0].positions[0] = -0.5f;
		quad[0].positions[1] = 0.5f;
		quad[1].positions[0] = -0.5f;
		quad[1].positions[1] = -0.5f;
		quad[2].positions[0] = 0.5f;
		quad[2].positions[1] = 0.5f;
		quad[3].positions[0] = 0.5f;
		quad[3].positions[1] = -0.5f;
	
		for(int i = 0; i < 4; ++i)
		{
			//Setting verts Z to 0 and clip value to 1
			quad[i].positions[2] = 0.0f;
			quad[i].positions[3] = 1.0f;
	
			//Setting colour to flat white with no transparency
			quad[i].colours[0] = 1.0f;
			quad[i].colours[1] = 1.0f;
			quad[i].colours[2] = 1.0f;
			quad[i].colours[3] = 1.0f;
		}
	
		//Setting UV positions
		quad[0].uv[0] = 0.0f;
		quad[0].uv[1] = 1.0f;
		quad[1].uv[0] = 0.0f;
		quad[1].uv[1] = 0.0f;
		quad[2].uv[0] = 1.0f;
		quad[2].uv[1] = 1.0f;
		quad[3].uv[0] = 1.0f;
		quad[3].uv[1] = 0.0f;
	
		//Create IDs for VBO
		glGenBuffers(1, &vbo);
	
		if(vbo != 0)
		{
			//Bind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			//Allocate space for verts on GPU
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*4, quad, GL_STATIC_DRAW);
			//Unbind the buffer
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	
		//We don't need the quad data in RAM anymore now it's been moved to the GPU.
		delete[4] quad;
		
		//Temp shader creation function
		shaderProgram->CreateProgram("Shaders/VertexShader.glsl", "Shaders/TexturedFragmentShader.glsl");
	}
	
	void Sprite::Draw()
	{
		//Use shader program
		shaderProgram->UseProgram();
	
		//Bind the texture
		glBindTexture(GL_TEXTURE_2D, textureID);
	
		//Bind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
		//Enable vertex array states for shader (AttribArray and AttribPointer)
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*4));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*8));
	
		//Draw elements
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
		//Unbind buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	}
	
	//temp function
	void Sprite::loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
	{
		unsigned int uiTextureID = 0;
		//check file exists
		if(a_pFilename != nullptr)
		{
			//read in image data from file
			unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);
	
			//check for successful read
			if(pImageData)
			{
				//create opengl texture handle
				uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
					SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS| SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				//clear what was read in from file now that it is stored in the handle
				SOIL_free_image_data(pImageData);
			}
	
			//check for errors
			if(uiTextureID == 0)
			{
				std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
			}
			textureID = uiTextureID;
		}
	}
	
	Sprite::~Sprite()
	{
		//deleting the IBO data
		glDeleteBuffers(1, &vbo);
		delete shaderProgram;
	}
}
