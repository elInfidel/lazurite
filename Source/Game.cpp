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
	camera->SetPerspective(70.0f, 16.0f / 9.0f, 1.0f, 100.0f);
	camera->transform.SetTranslation(vec3(0,0,-4));

	modelShader = new ShaderProgram();
	modelShader->CompileShader("Resources/Shaders/BlinnPhongVert.glsl", OpenGLShader::VERTEX);
	modelShader->CompileShader("Resources/Shaders/BlinnPhongFrag.glsl", OpenGLShader::FRAGMENT);
	modelShader->Link();
	modelShader->Validate();

	model = new Model("Resources/Models/stanford/Dragon.fbx");

	// Setting up tweak bar
	bar = TwNewBar("Debug Console");
	TwAddVarRO(bar, "FPS", TW_TYPE_FLOAT, &fps, "group=Performance");
	TwAddVarRW(bar, "Sun Direction", TW_TYPE_DIR3F, &lightDir, "group=Lighting");
	lightDir = vec3(0, 1, 0);
	TwAddVarRW(bar, "Ambient", TW_TYPE_COLOR3F, &matA, "group=Material");
	matA = vec3(0.0f, 0.15f, 0.30f);
	TwAddVarRW(bar, "Diffuse", TW_TYPE_COLOR3F, &matD, "group=Material");
	matD = vec3(0.0, 0.50f, 0.85f);
	TwAddVarRW(bar, "Specular", TW_TYPE_COLOR3F, &matS, "group=Material");
	matS = vec3(0.0f);
	TwAddVarRW(bar, "Specular Power", TW_TYPE_FLOAT, &specularPower, "group=Material");
	specularPower = 280.0;
	TwAddSeparator(bar, "Rim Light", "group=Material");
	TwAddVarRW(bar, "Rim Color", TW_TYPE_COLOR3F, &rimCol, "group=Material");
	rimCol = vec3(0.0, 0.40f, 0.80f);
	TwAddVarRW(bar, "Rim Power", TW_TYPE_FLOAT, &rimPow, "group=Material");
	rimPow = 20.0f;
}

void Game::Update(float deltaTime)
{
	camera->Update(deltaTime);
	fps = 1.0f / deltaTime;
}

void Game::Draw(float deltaTime)
{
	modelShader->Use();
	modelShader->SetUniform("vpMat", camera->GetProjectionView());
	modelShader->SetUniform("mvMat", camera->GetView() * model->transform.GetWorldMatrix());
	modelShader->SetUniform("pMat", camera->GetProjection());
	modelShader->SetUniform("vMat", camera->GetView());
	modelShader->SetUniform("matA", matA);
	modelShader->SetUniform("matD", matD);
	modelShader->SetUniform("matS", matS);
	modelShader->SetUniform("specPow", specularPower);
	modelShader->SetUniform("rimColor", rimCol);
	modelShader->SetUniform("rimPower", rimPow);
	modelShader->SetUniform("lightDir", glm::normalize(lightDir));
	model->Draw(*modelShader);
}

void Game::Unload()
{
	delete model;
	delete modelShader;
	delete camera;
}