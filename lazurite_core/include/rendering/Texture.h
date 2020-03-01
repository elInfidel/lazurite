#pragma once
#include <string>

using std::string;

namespace TextureType
{
	enum Type : int
	{
		Diffuse = 0,
		Albedo,
		Metallic,
		Roughness,
		Specular,
		Ambient,
		AmbientOcclusion,
		Emissive,
		Height,
		Normal,
		Shininess,
		Opacity,
		Displacement,
		Lightmap,
		Reflection,
		Unknown,
		TextureCount
	};

	// Stores string representation of each type.
	// Should be accessed using enumeration as offset.
	static const char* strings[] = 
	{ 
		"diffuse", 
		"albedo",
		"metallic",
		"roughness",
		"specular", 
		"ambient",
		"ambientOcclusion",
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

	void LoadTexture(string directory, const char* filePath, TextureType::Type type);

	bool Is1D() const;
	bool Is2D() const;
	bool Is3D() const;

	unsigned int GetID() const;

	int GetWidth()  const;
	int GetHeight() const;
	int GetDepth()  const;

	TextureType::Type GetType() const;

protected:
	void LoadOpenGLData(unsigned char* data);

	TextureType::Type type;

	unsigned int textureID;
	int width, height, depth;
	int  imageFormat;
};

