#include "Game.h"
#include "Subsystem/Input.h"
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Game::Load()
{

}

void Game::Tick(float deltaTime)
{

}

void Game::Draw(float deltaTime)
{
	if (Input::GetInstance()->GetKeyPressed(GLFW_KEY_GRAVE_ACCENT))
		developerMenu = (developerMenu) ? false : true;

	//Draw scene inspector
	if (developerMenu && ImGui::BeginMainMenuBar())
	{
		/*
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Profiling"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		*/
		ImGui::EndMainMenuBar();
	}
}

void Game::Unload()
{

}