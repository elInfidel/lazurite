#pragma once
#include "Texture.h"
#include "Vertex.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "component\Camera.h"
#include "Material.h"
#include <vector>
#include <memory>


class Primitive
{
public:
	Primitive(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::shared_ptr<MaterialBase> material);
	virtual ~Primitive();

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::shared_ptr<MaterialBase> material;

	void Draw(Camera& camera, Transform& camTransform, Transform& modelTransform) const;

private:
	GLuint vao, vbo, ebo;
};