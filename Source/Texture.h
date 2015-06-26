#pragma once
#include <string>

using namespace std;

class Texture
{
public:
	Texture();
	Texture(const char* filePath);
	virtual ~Texture();

	void LoadTexture(const char* filePath);

	bool Is1D() const;
	bool Is2D() const;
	bool Is3D() const;

	unsigned int GetID() const;

	int GetWidth()  const;
	int GetHeight() const;
	int GetDepth()  const;

protected:
	void LoadOpenGLData(unsigned char* data);

	unsigned int textureID;
	int width, height, depth;
	int  imageFormat;
};

