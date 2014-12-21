// ---------------------------------------------------------------------------
// Sprite.cpp
// A class for rendering a 2D image to the screen.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#include "Engine/Sprite.h"
#include <iostream>
#include "Engine/ShaderProgram.h"
#include "Math/Matrix4x4.h"
#include "GL/glfw3.h"
#include "Engine/Vertex.h"

// Includes below this line are temporary
// to support texturing until a class is developed to contain them
#include "SOIL/SOIL.h"

namespace lazurite
{
	Sprite::Sprite()
	{
		// Creating a shader program
		shaderProgram = new ShaderProgram();
		// Creating a transform for this sprite
		transform = Transform();

		// Creating a quad
		VertPosColorUV* quad = new VertPosColorUV[4];
	
		// Setting verts X Y coords
		quad[0].positions[0] = -100.0f;
		quad[0].positions[1] = 100.0f;
		quad[1].positions[0] = -100.0f;
		quad[1].positions[1] = -100.0f;
		quad[2].positions[0] = 100.0f;
		quad[2].positions[1] = 100.0f;
		quad[3].positions[0] = 100.0f;
		quad[3].positions[1] = -100.0f;
	
		for(int i = 0; i < 4; ++i)
		{
			// Setting verts Z to 0 and clip value to 1
			quad[i].positions[2] = 0.0f;
			quad[i].positions[3] = 1.0f;
	
			// Setting colour to flat white with no transparency
			quad[i].colours[0] = 1.0f;
			quad[i].colours[1] = 1.0f;
			quad[i].colours[2] = 1.0f;
			quad[i].colours[3] = 1.0f;
		}
	
		// Setting UV positions
		quad[0].uv[0] = 0.0f;
		quad[0].uv[1] = 1.0f;
		quad[1].uv[0] = 0.0f;
		quad[1].uv[1] = 0.0f;
		quad[2].uv[0] = 1.0f;
		quad[2].uv[1] = 1.0f;
		quad[3].uv[0] = 1.0f;
		quad[3].uv[1] = 0.0f;
	
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Create IDs for VBO
		glGenBuffers(1, &vbo);

		// Making sure the VBO has been generated
		if(vbo != 0)
		{
			// Bind the VBO
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// Allocate space for verts on GPU
			glBufferData(GL_ARRAY_BUFFER, sizeof(VertPosColorUV)*4, quad, GL_STATIC_DRAW);

			// Set up Shader attribute pointer information
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertPosColorUV), (void*)0);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertPosColorUV), (void*)(sizeof(float)*4));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertPosColorUV), (void*)(sizeof(float)*8));
			
			// Enable shader required shader attribute pointers
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			// Unbind the buffer
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	
		//Unbinding vertex array
		glBindVertexArray(0);

		// We don't need the quad data in RAM anymore now it's been moved to the GPU.
		delete[4] quad;
		
		// Temp shader creation functionality
		shaderProgram->CreateProgram("Shaders/SpriteVert.glsl", "Shaders/SpriteTexFrag.glsl");
		uniformLocation = glGetUniformLocation(shaderProgram->GetProgramID(), "MVP");
	}
	
	Sprite::~Sprite()
	{
		// Deleting the IBO data
		glDeleteBuffers(1, &vbo);
		delete shaderProgram;
	}

	void Sprite::Draw()
	{
		// Use shader program
		shaderProgram->UseProgram();
		
		// Passing matrix transformation into shader
		Matrix4x4 projection = lazmath::Matrix4x4::Ortho(0, 1024,0 , 768, 0.0f, 100.0f);
		Matrix4x4 model = transform.GetTransformation();
		Matrix4x4 mvp = projection * model;
		glUniformMatrix4fv(uniformLocation, 1, GL_TRUE, &mvp.m_matrix[0][0]);

		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, textureID);
	
		glBindVertexArray(vao);

		// Draw elements
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
		// Unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	}
	
	// temp function
	void Sprite::loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
	{
		unsigned int uiTextureID = 0;
		// Check file exists
		if(a_pFilename != nullptr)
		{
			// Read in image data from file
			unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);
	
			// Check for successful read
			if(pImageData)
			{
				// Create opengl texture handle
				uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
					SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS| SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				// Clear what was read in from file now that it is stored in the handle
				SOIL_free_image_data(pImageData);
			}
	
			// Check for errors
			if(uiTextureID == 0)
			{
				std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
			}
			textureID = uiTextureID;
		}
	}
}
