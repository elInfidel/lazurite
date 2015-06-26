#include "Texture.h"
#include "loadgen/gl_core_4_4.h"
#include "stb/stb_image.h"
#include <iostream>

Texture::Texture() : width(0), height(0), depth(0), imageFormat(0)
{

}

Texture::Texture(const char* filePath) : width(0), height(0), depth(0), imageFormat(0)
{
	LoadTexture(filePath);
}

Texture::~Texture()
{

}

void Texture::LoadTexture(const char* filePath)
{
	LoadOpenGLData(stbi_load(filePath, &width, &height, &imageFormat, STBI_default));
}

void Texture::LoadOpenGLData(unsigned char* data)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

bool Texture::Is1D() const
{
	return (height > 0);
}

bool Texture::Is2D() const
{
	return (height > 0 && width > 0);
}

bool Texture::Is3D() const
{
	return (height > 0 && width > 0 && depth > 0);
}

unsigned int Texture::GetID() const
{
	return textureID;
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}

int Texture::GetDepth() const
{
	return depth;
}
