#pragma once
#include "ShaderProgram.h"
#include "Camera.h"

class Cubemap
{
public:
	Cubemap(const char* front, const char* back, const char* top, const char* bottom,
			const char* left, const char* right);
	~Cubemap();

	void Draw(const ShaderProgram& shaderProgram, const Camera* camera);
private:
	unsigned int vbo, vao;
	GLuint texHandle;

	void CreateCubemap(const char* front, const char* back, const char* top, const char* bottom,
					   const char* left, const char* right, GLuint* texCube);
	bool LoadCubemapFace(unsigned int texHandle, GLenum faceTarget, const char* fileName);
};

