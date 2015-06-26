#include "Plane.h"
#include "loadgen/gl_core_4_4.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"
#include "Vertex.h"
#include <iostream>

Plane::Plane(int dimensions) : vao(0), vbo(0), ibo(0), dimensions(0)
{
	GenerateMesh(dimensions);
}


Plane::~Plane()
{
}

void Plane::GenerateMesh(int dimensions)
{
	this->dimensions = dimensions;

	Vertex* vertices = new Vertex[dimensions * dimensions];
	for (unsigned int x = 0; x < (unsigned int)dimensions; ++x)
	{
		for (unsigned int y = 0; y < (unsigned int)dimensions; ++y)
		{
			vertices[x * dimensions + y].position = vec3((float)y, 0, (float)x);
			vertices[x * dimensions + y].texCoord1 = vec2(x / (float)dimensions, y / (float)dimensions);
		}
	}

	// defining index count based off quad count (2 triangles per quad)
	unsigned int* indices = new unsigned int[(dimensions - 1) * (dimensions - 1) * 6];
	unsigned int index = 0;

	for (unsigned int r = 0; r < ((unsigned int)dimensions - 1); ++r)
	{
		for (unsigned int c = 0; c < ((unsigned int)dimensions - 1); ++c)
		{
			// triangle 1
			indices[index++] = r * dimensions + c;
			indices[index++] = (r + 1) * dimensions + c;
			indices[index++] = (r + 1) * dimensions + (c + 1);
			// triangle 2
			indices[index++] = r * dimensions + c;
			indices[index++] = (r + 1) * dimensions + (c + 1);
			indices[index++] = r * dimensions + (c + 1);
		}
	}

	// Generate and bind vao, vbo and ibo
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (dimensions * dimensions) * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ((dimensions - 1) * (dimensions - 1)) * 6 * sizeof(int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1); // Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
	glEnableVertexAttribArray(2); // TexCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4) * 2));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] vertices;
	delete[] indices;
}

void Plane::Draw(ShaderProgram* shaderProgram, Camera* camera)
{
	shaderProgram->Use();

	shaderProgram->SetUniform("projectionView", camera->GetProjectionView());
	shaderProgram->SetUniform("modelView", (camera->GetView() * glm::mat4(1)));
	shaderProgram->SetUniform("cameraPos", camera->transform->GetPosition());
	shaderProgram->SetUniform("model", glm::mat4(1));
	shaderProgram->SetUniform("time", (float)glfwGetTime());

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (((dimensions - 1) * (dimensions - 1)) * 6), GL_UNSIGNED_INT, 0);
}
