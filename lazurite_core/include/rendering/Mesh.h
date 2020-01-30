#pragma once
#include "gl_core_4_4.h"
#include "Texture.h"
#include "Vertex.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Material.h"
#include <vector>
#include <component\Camera.h>

using namespace std;

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, MaterialBase* material);
	~Mesh();

	vector<Vertex> vertices;
	vector<GLuint> indices;
	MaterialBase* material;

	void Draw(const mat4& view, const mat4& projection, const mat4& model);

private:
	GLuint vao, vbo, ebo;
	void SetupMesh();
};