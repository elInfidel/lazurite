#pragma once
#include <string>

using std::string;

namespace TextureType
{
	enum Type : int
	{
		Diffuse          = 0,
		Specular         = 1,
		Ambient          = 2,
		Emissive         = 3,
		Height           = 4,
		Normal           = 5,
		Shininess        = 6,
		Opacity          = 7,
		Displacement     = 8,
		Lightmap         = 9,
		Reflection       = 10,
		Unknown          = 11,
		TextureCount     = 12
	};

	// Stores string representation of each type.
	// Should be accessed using enumeration as offset.
	static const char* strings[] = 
	{ 
		"diffuse", 
		"specular", 
		"ambient",
		"emissive",
		"height",
		"normal",
		"shininess",
		"opacity",
		"displacement",
		"lightmap",
		"reflection",
		"unknown"
	};
}

class Texture
{
public:
	Texture();
	Texture(string directory, const char* filePath);
	virtual ~Texture();

	void LoadTexture(string directory, const char* filePath);

	bool Is1D() const;
	bool Is2D() const;
	bool Is3D() const;

	unsigned int GetID() const;

	int GetWidth()  const;
	int GetHeight() const;
	int GetDepth()  const;

	// Temp
	TextureType::Type type;

protected:
	void LoadOpenGLData(unsigned char* data);

	unsigned int textureID;
	int width, height, depth;
	int  imageFormat;
};

