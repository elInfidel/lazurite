#include "Cubemap.h"
#include "loadgen/gl_core_4_4.h"
#include "stb/stb_image.h"
#include "glm/gtc/matrix_transform.hpp"

Cubemap::Cubemap(const char* front, const char* back, const char* top, const char* bottom,
				 const char* left, const char* right)
{
	float points[] = {
		-100.0f, 100.0f, -100.0f,
		-100.0f, -100.0f, -100.0f,
		100.0f, -100.0f, -100.0f,
		100.0f, -100.0f, -100.0f,
		100.0f, 100.0f, -100.0f,
		-100.0f, 100.0f, -100.0f,

		-100.0f, -100.0f, 100.0f,
		-100.0f, -100.0f, -100.0f,
		-100.0f, 100.0f, -100.0f,
		-100.0f, 100.0f, -100.0f,
		-100.0f, 100.0f, 100.0f,
		-100.0f, -100.0f, 100.0f,

		100.0f, -100.0f, -100.0f,
		100.0f, -100.0f, 100.0f,
		100.0f, 100.0f, 100.0f,
		100.0f, 100.0f, 100.0f,
		100.0f, 100.0f, -100.0f,
		100.0f, -100.0f, -100.0f,

		-100.0f, -100.0f, 100.0f,
		-100.0f, 100.0f, 100.0f,
		100.0f, 100.0f, 100.0f,
		100.0f, 100.0f, 100.0f,
		100.0f, -100.0f, 100.0f,
		-100.0f, -100.0f, 100.0f,

		-100.0f, 100.0f, -100.0f,
		100.0f, 100.0f, -100.0f,
		100.0f, 100.0f, 100.0f,
		100.0f, 100.0f, 100.0f,
		-100.0f, 100.0f, 100.0f,
		-100.0f, 100.0f, -100.0f,

		-100.0f, -100.0f, -100.0f,
		-100.0f, -100.0f, 100.0f,
		100.0f, -100.0f, -100.0f,
		100.0f, -100.0f, -100.0f,
		-100.0f, -100.0f, 100.0f,
		100.0f, -100.0f, 100.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	CreateCubemap(front, back, top, bottom, left, right, &texHandle);
}


Cubemap::~Cubemap()
{

}

void Cubemap::Draw(const ShaderProgram& shaderProgram, const Camera* camera)
{
	glDepthMask(GL_FALSE);
	glUseProgram(shaderProgram.GetHandle());
	shaderProgram.SetUniform("P", camera->GetProjection());
	shaderProgram.SetUniform("V", glm::mat4(glm::mat3(camera->GetView())));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texHandle);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

void Cubemap::CreateCubemap(const char* front, const char* back, const char* top, const char* bottom,
						    const char* left, const char* right, GLuint* texCube)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, texCube);

	// Load faces of the cubemap
	LoadCubemapFace(*texCube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	LoadCubemapFace(*texCube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	LoadCubemapFace(*texCube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	LoadCubemapFace(*texCube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	LoadCubemapFace(*texCube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	LoadCubemapFace(*texCube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);

	// Format the cubemap texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool Cubemap::LoadCubemapFace(GLuint texHandle, GLenum faceTarget, const char* fileName)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texHandle);

	int x, y, n;
	int force_channels = 4;
	unsigned char*  image_data = stbi_load(fileName, &x, &y, &n, force_channels);
	if (!image_data) 
	{
		fprintf(stderr, "ERROR: could not load %s\n", fileName); // TODO:(Liam) Replace with framework logging tools
		return false;
	}

	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0)
		fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n", fileName); // TODO:(Liam) Replace with framework logging tools

	// copy image data into 'target' side of cube map
	glTexImage2D(
		faceTarget,
		0,
		GL_RGBA,
		x,
		y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image_data
		);

	free(image_data);
	return true;
}
