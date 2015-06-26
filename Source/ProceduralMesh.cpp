#include "ProceduralMesh.h"
#include "glm/gtc/noise.hpp"
#include "glfw/glfw3.h"
#include <iostream>

ProceduralMesh::ProceduralMesh(int dimensions, int newSeed) : Plane(dimensions), seed(newSeed), octaves(6), amplitude(48), frequency(3), heightmapID(0)
{
	lightDirection = vec3(0,-1,0);
	GenerateTextures();
}

ProceduralMesh::~ProceduralMesh()
{
	delete grass;
	delete rock;
	delete snow;
}

void ProceduralMesh::GenerateHeightMap()
{
	if (dimensions == 0) return;

	float *perlin_data = new float[dimensions * dimensions];
	float scale = (1.0f / dimensions) * 3;
	for (size_t x = 0; x < dimensions; ++x)
	{
		for (size_t y = 0; y < dimensions; ++y)
		{
			float amp = amplitude;
			float persistence = 0.3f;
			perlin_data[y * dimensions + x] = 0;

			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(frequency, (float)o);
				float perlin_sample = glm::perlin(vec2((float)x, (float)y) * scale * freq);
				perlin_data[y * dimensions + x] += perlin_sample * amp;
				amp *= persistence;
			}
		}
	}

	glGenTextures(1, &heightmapID);
	glBindTexture(GL_TEXTURE_2D, heightmapID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, dimensions, dimensions, 0, GL_RED, GL_FLOAT, perlin_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	delete perlin_data;
}

void ProceduralMesh::GenerateTextures()
{
	//if (dimensions == 0) return;
	grass = new Texture("./Resources/Grass.jpg");
	rock =  new Texture("./Resources/Rock.jpg");
	snow =  new Texture("./Resources/Snow.jpg");
}

void ProceduralMesh::Draw(ShaderProgram* shaderProgram, Camera* camera)
{
	shaderProgram->Use();

	// Setting texture samplers
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, heightmapID);
	shaderProgram->SetUniform("heightMap", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, grass->GetID());
	shaderProgram->SetUniform("grass", 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, rock->GetID());
	shaderProgram->SetUniform("rock", 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, snow->GetID());
	shaderProgram->SetUniform("snow", 3);

	// Setting environment and generation variables
	shaderProgram->SetUniform("projectionView", camera->GetProjectionView());
	shaderProgram->SetUniform("modelView", (camera->GetView() * glm::mat4(1)));
	shaderProgram->SetUniform("cameraPos", camera->transform->GetPosition());
	shaderProgram->SetUniform("lightDir", lightDirection);
	shaderProgram->SetUniform("model", glm::mat4(1));
	shaderProgram->SetUniform("time", (float)glfwGetTime());
	shaderProgram->SetUniform("seed", (float)seed);
	shaderProgram->SetUniform("octaves", octaves);
	shaderProgram->SetUniform("amplitude", amplitude);
	shaderProgram->SetUniform("frequency", frequency);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (((dimensions - 1) * (dimensions - 1)) * 6), GL_UNSIGNED_INT, 0);
}
