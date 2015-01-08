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
	GLuint Sprite::vao = 0;
	GLuint Sprite::vbo = 0;
	GLuint Sprite::ibo = 0;
	GLuint Sprite::instances = 0;

	Sprite::Sprite()
	{
		++instances;

		// Creating a shader program
		shaderProgram = new ShaderProgram();
		// Creating a transform for this sprite
		transform = Transform();

		// Temp shader creation functionality
		shaderProgram->CreateProgram("Shaders/BasicVert.glsl", "Shaders/SpriteTexFrag.glsl");
		uniformLocation = glGetUniformLocation(shaderProgram->GetProgramID(), "MVP");

		if(instances > 1)
			return;

		// Creating a quad
		VertPosColorUV quad[4];
	
		// Setting verts X Y coords
		quad[0].positions[0] = -50.0f;
		quad[0].positions[1] = 50.0f;
		quad[1].positions[0] = -50.0f;
		quad[1].positions[1] = -50.0f;
		quad[2].positions[0] = 50.0f;
		quad[2].positions[1] = 50.0f;
		quad[3].positions[0] = 50.0f;
		quad[3].positions[1] = -50.0f;
	
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
		
		// Creating index array

		GLuint indexArray[] = {0, 1, 2, 1, 3, 2};

		// Create Vertex object to store buffers
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Generate buffer objects
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ibo);

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

		}
		
		if(ibo != 0)
		{
			// Bind the IBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);
		}

		//Unbinding vertex array and buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	Sprite::~Sprite()
	{
		// Deleting the IBO data
		glDeleteBuffers(1, &vbo);
		delete shaderProgram;
		--instances;
	}

	void Sprite::Draw()
	{
		// Setting filtering mode
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Use shader program
		shaderProgram->UseProgram();
		
		// Passing matrix transformation into shader
		// We calculate the MVP on the CPU instead of doing it in the shader
		Matrix4x4 projection = lazmath::Matrix4x4::Ortho(0, 1920,0 , 1080, 0.0f, 100.0f);
		Matrix4x4 model = transform.GetTransformation();
		Matrix4x4 mvp = projection * model;
		glUniformMatrix4fv(uniformLocation, 1, GL_TRUE, &mvp.m_matrix[0][0]);

		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, textureID);
	
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// Draw elements
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
		// Unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	// temp function
	void Sprite::SetTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
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
					SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS| SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB);
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
