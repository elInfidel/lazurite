#include "Game.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "FlyCamera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Core/Input.h"
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Game::Load()
{
	transform = obj.GetComponent<Transform>();
	std::cout << transform.lock().get()->GetPosition().x << std::endl;
}

void Game::Tick(float deltaTime)
{

}

void Game::Draw(float deltaTime)
{
	//Draw scene inspector
	ImGui::Begin("Scene Properties");
	ImGui::Spacing();
	ImGui::Text("Model Selection");
	ImGui::Spacing();
	ImGui::Text("Material Parameters");
	ImGui::SliderFloat3("Ambient", glm::value_ptr(matA), 0.0f, 1.0f);
	ImGui::SliderFloat3("Diffuse", glm::value_ptr(matD), 0.0f, 1.0f);
	ImGui::SliderFloat3("Specular", glm::value_ptr(matS), 0.0f, 1.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Specular Power", &specularPower, 0.1f, 256.0f);
	ImGui::Spacing();
	ImGui::SliderFloat("Rim Power", &rimPow, 0.1f, 100.0f);
	ImGui::SliderFloat3("Rim Color", glm::value_ptr(rimCol), 0.0f, 1.0f);
	ImGui::End();
}

void Game::Unload()
{

}