#pragma once
#include "gl_core_4_4.h"
#include "Texture.h"
#include "Vertex.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Material.h"
#include <vector>

using namespace std;

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, Material material);
	virtual ~Mesh();

	vector<Vertex> vertices;
	vector<GLuint> indices;
	Material material;

	void Draw(const ShaderProgram& shaderProgram) const;

private:
	GLuint vao, vbo, ebo;

	void SetupMesh();

};