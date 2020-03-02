#include "rendering/Texture.h"
#include "gl_core_4_4.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <sys/stat.h>
#include <iostream>

Texture::Texture() : type(TextureType::Unknown), textureID(0), width(0), height(0), depth(0), imageFormat(0)
{

}

Texture::Texture(string directory, const char* filePath) : width(0), height(0), depth(0), imageFormat(0)
{
	LoadTexture(directory, filePath, TextureType::Unknown);
}

Texture::~Texture()
{

}

void Texture::LoadTexture(string directory, const char* filePath, TextureType::Type type)
{
	string path = string(filePath);

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &imageFormat, 0);

	if (!data) {
		std::cout << "Failed to load texture at path: " << path << std::endl;
		stbi_image_free(data);
		return;
	};

	this->type = type;

	LoadOpenGLData(data);
	stbi_image_free(data);
}

/* TODO: Draw this code out into subclass of an interface that can support other rendering libraries*/
void Texture::LoadOpenGLData(unsigned char* data)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	GLenum format = GL_RGBA;
	if (imageFormat == 1)
		format = GL_RED;
	else if (imageFormat == 3)
		format = GL_RGB;
	else if (imageFormat == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
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

TextureType::Type Texture::GetType() const
{
	return type;
}
