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
	camera->SetPerspective(70.0f, 16 / 9.f, 1.0f, 10000.0f);
	camera->transform->SetPosition(vec3(0,0,0));

	shaderProgram = new ShaderProgram();
	shaderProgram->CompileShader("Resources/Shaders/CubemapVert.glsl", OpenGLShader::VERTEX);
	shaderProgram->CompileShader("Resources/Shaders/CubemapFrag.glsl", OpenGLShader::FRAGMENT);
	shaderProgram->Link();
	shaderProgram->Validate();

	modelShader = new ShaderProgram();
	modelShader->CompileShader("Resources/Shaders/BRDFVert.glsl", OpenGLShader::VERTEX);
	modelShader->CompileShader("Resources/Shaders/BRDFFrag.glsl", OpenGLShader::FRAGMENT);
	modelShader->Link();
	modelShader->Validate();

	model = new Model("Resources/Models/jc_body/JC_Cygirl.fbx");

	cubeMap = new Cubemap("Resources/Textures/Cubemaps/Yokohama/negz.jpg", "Resources/Textures/Cubemaps/Yokohama/posz.jpg", "Resources/Textures/Cubemaps/Yokohama/posy.jpg",
						  "Resources/Textures/Cubemaps/Yokohama/negy.jpg", "Resources/Textures/Cubemaps/Yokohama/negx.jpg", "Resources/Textures/Cubemaps/Yokohama/posx.jpg");

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

	modelShader->Use();
	modelShader->SetUniform("viewProjection", camera->GetProjectionView());
	modelShader->SetUniform("lightDir", glm::normalize(lightDir));
	model->Draw(*modelShader);
}

void Game::Unload()
{
	delete model;
	delete modelShader;
	delete camera;
	delete cubeMap;
	delete shaderProgram;
}