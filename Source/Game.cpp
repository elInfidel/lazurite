#include "Game.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "FlyCamera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Core/Input.h"
#include "GameObject.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Game::Load()
{
	// Initialize camera
	camera = new FlyCamera();
	camera->SetPerspective(70.0f, 16.0f / 9.0f, 1.0f, 100.0f);
	camera->transform.SetPosition(vec3(0,4,12));

	modelShader = new ShaderProgram();
	modelShader->CompileShader("Resources/Shaders/BlinnPhongVert.glsl", OpenGLShader::VERTEX);
	modelShader->CompileShader("Resources/Shaders/BlinnPhongFrag.glsl", OpenGLShader::FRAGMENT);
	modelShader->Link();
	modelShader->Validate();
	model = new Model("Resources/Models/stanford/Bunny.fbx");
}

void Game::Update(const Scene& scene, float deltaTime)
{
	camera->Update(deltaTime);
}

void Game::Draw(float deltaTime)
{
	mat4 viewMatrix = camera->GetViewMatrix();
	mat4 projectionMatrix = camera->GetProjectionMatrix();
	mat4 modelMatrix = model->transform.GetWorldMatrix();

	//Draw scene inspector
	ImGui::Begin("Scene Properties");
	ImGui::Spacing();
	ImGui::Text("Model");
	ImGui::SliderFloat3("Ambient", glm::value_ptr(matA), 0.0f, 1.0f);
	ImGui::SliderFloat3("Diffuse", glm::value_ptr(matD), 0.0f, 1.0f);
	ImGui::SliderFloat3("Specular", glm::value_ptr(matS), 0.0f, 1.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Specular Power", &specularPower, 0.0f, 128.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Rim Power", &rimPow, 0.0f, 10.0f);
	ImGui::SliderFloat3("Rim Color", glm::value_ptr(rimCol), 0.0f, 1.0f);
	ImGui::End();

	//Draw model
	modelShader->Use();
	modelShader->SetUniform("mMat", modelMatrix);
	modelShader->SetUniform("vMat", viewMatrix);
	modelShader->SetUniform("pMat", projectionMatrix);
	modelShader->SetUniform("mvMat", viewMatrix * modelMatrix);
	modelShader->SetUniform("mvpMat", projectionMatrix * viewMatrix * modelMatrix);

	modelShader->SetUniform("matAmbient", matA);
	modelShader->SetUniform("matDiffuse", matD);
	modelShader->SetUniform("matSpecular", matS);

	modelShader->SetUniform("specPow", specularPower);
	modelShader->SetUniform("rimColor", rimCol);
	modelShader->SetUniform("rimPower", rimPow);
	modelShader->SetUniform("lightPos", lightPos);
	model->Draw(*modelShader);
}

void Game::Unload()
{
	delete model;
	delete modelShader;

	delete camera;
}