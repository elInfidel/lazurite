#pragma once
#include "ShaderProgram.h"
#include "Camera.h"

class Plane
{
public:
	Plane(int dimensions);
	virtual ~Plane();

	virtual void Plane::Draw(ShaderProgram* shaderProgram, Camera* camera);

protected:
	unsigned int dimensions, vao, vbo, ibo;

private:
	void GenerateMesh(int dimensions);

};

