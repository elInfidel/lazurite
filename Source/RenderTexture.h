#pragma once
#include "Texture.h"

class RenderTexture : Texture
{
public:
	RenderTexture();
	RenderTexture(int width, int height);
	~RenderTexture();

private:
	unsigned int fboID, fboDepth;
};

