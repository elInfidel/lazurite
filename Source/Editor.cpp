#include "Editor.h"
#include "Subsystem/Input.h"
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Editor::Load()
{

}

void Editor::Tick(float deltaTime)
{

}

void Editor::Draw(float deltaTime)
{
	if (Input::GetInstance()->GetKeyPressed(GLFW_KEY_GRAVE_ACCENT))
		developerMenu = (developerMenu) ? false : true;

	//Draw scene inspector
	if (developerMenu && ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene", "CTRL+N")) {}
			if (ImGui::MenuItem("Save Scene", "CTRL+S")) {}
			if (ImGui::MenuItem("Save Scene As...", "CTRL+Z")) {}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Profiler")) {}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("New Scene", "CTRL+N")) {}
			if (ImGui::MenuItem("Save Scene", "CTRL+S")) {}
			if (ImGui::MenuItem("Save Scene As...", "CTRL+Z")) {}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void Editor::Unload()
{

}