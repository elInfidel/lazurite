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
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, MaterialBase* material);
	virtual ~Mesh();

	vector<Vertex> vertices;
	vector<GLuint> indices;
	MaterialBase* material;

	void Draw() const;

private:
	GLuint vao, vbo, ebo;
	void SetupMesh();
};