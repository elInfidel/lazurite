#pragma once
#include "Texture.h"
#include "Vertex.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Material.h"
#include <vector>
#include <component\Camera.h>

using namespace std;

class Mesh : public AComponent
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, MaterialBase* material);
	virtual ~Mesh();

	vector<Vertex> vertices;
	vector<GLuint> indices;
	MaterialBase* material;

	void Draw(Camera& camera, Transform& camTransform, Transform& modelTransform) const;

private:

	// Abstract this behind some sort of rendering system interface.
	GLuint vao, vbo, ebo;
	
	void SetupMesh();
};