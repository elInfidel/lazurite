#include "Editor.h"
#include "Subsystem/Input.h"
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Editor::TickMainMenuBar()
{
	//Draw scene inspector
	if (developerMenu && ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene", "CTRL+N")) {}
			if (ImGui::MenuItem("Save Scene", "CTRL+S")) {}
			if (ImGui::MenuItem("Save Scene As...")) {}
			if (ImGui::MenuItem("Load Scene", "CTRL+L")) {}
			if (ImGui::MenuItem("Exit", "ALT+F4")) {}

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
			if (ImGui::MenuItem("Hierarchy")) {}
			if (ImGui::MenuItem("Profiler")) {}
			if (ImGui::MenuItem("Lua Console")) {}


			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void Editor::Load()
{

}

void Editor::Tick(float deltaTime)
{
	if (Input::GetInstance()->GetKeyPressed(GLFW_KEY_GRAVE_ACCENT))
		developerMenu = (developerMenu) ? false : true;

	TickMainMenuBar();
}

void Editor::Draw(float deltaTime)
{

}

void Editor::Unload()
{

}