#include "rendering/Primitive.h"
#include <iostream>
#include <subsystem\Input.h>
#include "GameObject.h"

Primitive::Primitive(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::shared_ptr<MaterialBase> material)
	: vertices(vertices), indices(indices), material(material)
{
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Vertex position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::PositionOffset);
	glEnableVertexAttribArray(1); // Vertex normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)VertexOffset::NormalOffset);
	glEnableVertexAttribArray(2); // Vertex texcoord1
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::TexCoord1Offset);

	glBindVertexArray(0);
}


Primitive::~Primitive()
{
}

void Primitive::Draw(Camera& camera, Transform& camTransform, Transform& modelTransform) const
{
	if (material) {
		ShaderProgram& program = material->getShaderProgram();

		program.Use();

		// Set any uniforms
		program.SetUniform("model", modelTransform.GetWorldMatrix());

		program.SetUniform("view", camera.GetViewMatrix());
		program.SetUniform("projection", camera.GetProjectionMatrix());

		vector<vec3> pointPositions = {
			vec3(0, 1, 5.f)
		};

		vector<vec3> pointColors = {
			vec3(255, 255, 255)
		};

		program.SetUniform("lightPositions", pointPositions);
		program.SetUniform("lightColors", pointColors);
		program.SetUniform("camPos", camTransform.GetPosition());

		// Set texture uniform values
		for (int i = 0; i < material->textures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + (unsigned int)i);
			string targetTexture = "texture_" + std::string(TextureType::strings[material->textures[i].GetType()]);
			program.SetUniform(targetTexture.c_str(), i);
			glBindTexture(GL_TEXTURE_2D, material->textures[i].GetID());
		}
	}

	// Render
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, (GLsizei)0);
	glBindVertexArray(0);
}