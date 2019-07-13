#include "Mesh.h"
#include <iostream>

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, Material material) 
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
	glEnableVertexAttribArray(1); // Vertex color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE,  sizeof(Vertex), (void*)VertexOffset::ColorOffset);
	glEnableVertexAttribArray(2); // Vertex normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE,  sizeof(Vertex), (void*)VertexOffset::NormalOffset);
	glEnableVertexAttribArray(3); // Vertex tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_TRUE,  sizeof(Vertex), (void*)VertexOffset::TangentOffset);
	glEnableVertexAttribArray(4); // Vertex bitangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::BiTangentOffset);
	glEnableVertexAttribArray(5); // Vertex indices
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::IndicesOffset);
	glEnableVertexAttribArray(6); // Vertex weights
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::WeightsOffset);
	glEnableVertexAttribArray(7); // Vertex texcoord1
	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::TexCoord1Offset);
	glEnableVertexAttribArray(8); // Vertex texcoord2
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)VertexOffset::TexCoord2Offset);

	glBindVertexArray(0);
}

void Mesh::Draw(const ShaderProgram& shaderProgram) const
{
	for (int i = 0; i < material.textures.size(); ++i)
	{
		if (material.textures[i].GetType() == TextureType::Opacity)
			shaderProgram.SetUniform("alphaTested", true);
		else
			shaderProgram.SetUniform("alphaTested", false);

		glActiveTexture(GL_TEXTURE0 + (unsigned int)i);
		shaderProgram.SetUniform(TextureType::strings[material.textures[i].GetType()], i);
		glBindTexture(GL_TEXTURE_2D, material.textures[i].GetID());
	}

	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, (GLsizei)0);
	glBindVertexArray(0);
}