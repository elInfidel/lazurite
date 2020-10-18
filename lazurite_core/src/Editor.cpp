#include "Editor.h"
#include "subsystem/Input.h"
#include "GLTFLoader.h"
#include <iostream>
#include <imgui.h>
#include <queue>

void Editor::Load()
{
	auto cameraPtr = camera.AddComponent<Camera>();
	camera.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0,1.5f,1));

	GLTFLoader loader;
	loader.Load("../../resources/models/box.gltf");
}

void Editor::Tick(float deltaTime)
{
	camera.GetComponent<Camera>().lock()->Tick(deltaTime);

	float camSpeed = 1;

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_W)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, camSpeed * deltaTime, 0));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_A)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(-camSpeed * deltaTime, 0, 0));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_S)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, -camSpeed * deltaTime, 0));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_D)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(camSpeed * deltaTime, 0, 0));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, 0, -camSpeed * deltaTime));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_LEFT_CONTROL)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, 0, camSpeed * deltaTime));
	}
}

void RenderDebugOverlay()
{
	static bool windowVisible = true;
	static bool showDemoWindow = false;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Exit");
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::MenuItem("Demo Window", NULL, &showDemoWindow);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if (showDemoWindow)
		ImGui::ShowDemoWindow(&showDemoWindow);
}

void Editor::Draw(float deltaTime)
{
	RenderDebugOverlay();
}

void Editor::Unload()
{

}