#include "Game.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "FlyCamera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Subsystem/Input.h"
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
	ImGui::BeginMainMenuBar();
	ImGui::BeginMenu("File");
	ImGui::BeginMenu("Profiling");
	ImGui::BeginMenu("Settings");
	ImGui::BeginMenu("Help");
	ImGui::End();
}

void Game::Unload()
{

}