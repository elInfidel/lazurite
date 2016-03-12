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
}

void Game::Update(float deltaTime)
{
	camera->Update(deltaTime);
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