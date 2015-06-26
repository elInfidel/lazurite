#pragma once
#include "loadgen/gl_core_4_4.h"
#include "Texture.h"
#include "Vertex.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include <vector>

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	virtual ~Mesh();

	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	void Draw(const ShaderProgram& shaderProgram) const;

private:
	GLuint vao, vbo, ebo;

	void SetupMesh();

};

