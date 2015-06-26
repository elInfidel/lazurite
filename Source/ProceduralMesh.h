#pragma once
#include "Camera.h"
#include "ShaderProgram.h"
#include "Plane.h"
#include "texture.h"

class ProceduralMesh : Plane
{
public:
	ProceduralMesh(int dimensions, int newSeed);
	~ProceduralMesh();
	
	void GenerateHeightMap();
	void GenerateTextures();

	void Draw(ShaderProgram* shaderProgram, Camera* camera);

	unsigned int heightmapID;
	Texture* grass;
	Texture* rock;
	Texture* snow;

	vec3 lightDirection;

	int seed;
	int octaves;
	float amplitude;
	float frequency;
};

