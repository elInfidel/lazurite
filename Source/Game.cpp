#include "Game.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "FlyCamera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Input.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Game::Load()
{
	// Initialize camera
	camera = new FlyCamera();
	camera->SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 1.0f, 10000.0f);

	shaderProgram = new ShaderProgram();
	shaderProgram->CompileShader("Resources/Shaders/CubemapVert.glsl", OpenGLShader::VERTEX);
	shaderProgram->CompileShader("Resources/Shaders/CubemapFrag.glsl", OpenGLShader::FRAGMENT);
	shaderProgram->Link();
	shaderProgram->Validate();

	cubeMap = new Cubemap("Resources/Textures/Cubemaps/Colosseum/negz.jpg", "Resources/Textures/Cubemaps/Colosseum/posz.jpg", "Resources/Textures/Cubemaps/Colosseum/posy.jpg",
						  "Resources/Textures/Cubemaps/Colosseum/negy.jpg", "Resources/Textures/Cubemaps/Colosseum/negx.jpg", "Resources/Textures/Cubemaps/Colosseum/posx.jpg");

	// Setting up tweak bar
	bar = TwNewBar("Debug Console");
	TwAddVarRO(bar, "FPS", TW_TYPE_FLOAT, &fps, "group=Performance");
	lightDir = vec3(0,1,0);
	TwAddVarRW(bar, "Sun Direction", TW_TYPE_DIR3F, &lightDir, "group=Lighting");
}

void Game::Update(float deltaTime)
{
	camera->Update(deltaTime);
	fps = 1.0f / deltaTime;
}

void Game::Draw(float deltaTime)
{
	cubeMap->Draw(*shaderProgram, camera);
}

void Game::Unload()
{
	delete camera;
	delete cubeMap;
	delete shaderProgram;
}