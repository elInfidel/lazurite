#include "rendering/Mesh.h"
#include <iostream>
#include <subsystem\Input.h>

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, MaterialBase* material) 
	: vertices(vertices), indices(indices), material(material)
{
	this->SetupMesh();
}


Mesh::~Mesh()
{
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Vertex position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::PositionOffset);
	glEnableVertexAttribArray(1); // Vertex normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE,  sizeof(Vertex), (void*)VertexOffset::NormalOffset);
	glEnableVertexAttribArray(2); // Vertex texcoord1
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::TexCoord1Offset);

	glBindVertexArray(0);
}

void Mesh::Draw(Camera& camera, Transform& camTransform, Transform& modelTransform) const
{
	if (material) {
		ShaderProgram& program = material->getShaderProgram();

		// Shader hacky reloading implementation
		if (Input::GetInstance()->GetKeyPressed(GLFW_KEY_R)) {
			program.Reload();
		}

		program.Use();

		// Set any uniforms
		program.SetUniform("model", modelTransform.GetWorldMatrix());
		program.SetUniform("view", camera.GetViewMatrix());
		program.SetUniform("projection", camera.GetProjectionMatrix());

		vector<vec3> pointPositions = {
			vec3(0, 0, 7)
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

		// Render
		glBindVertexArray(this->vao);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, (GLsizei)0);
		glBindVertexArray(0);
	}
}