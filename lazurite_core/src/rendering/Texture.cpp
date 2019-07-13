#include "rendering/Texture.h"
#include "gl_core_4_4.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>

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
	path = directory + "/" + path;
	this->type = type;

	LoadOpenGLData(stbi_load(path.c_str(), &width, &height, &imageFormat, STBI_rgb_alpha));
}

void Texture::LoadOpenGLData(unsigned char* data)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if (type == TextureType::Diffuse) // If texture is diffuse we use SRGB color space
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

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

TextureType::Type Texture::GetType() const
{
	return type;
}
