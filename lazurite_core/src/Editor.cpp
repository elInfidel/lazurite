#include "Editor.h"
#include "subsystem/Input.h"
#include <iostream>
#include <imgui.h>
#include <queue>

/*
#include <windows.h>
Hand little snippet for grabbing the working directory.
std::string workingdir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return string(buf);
}
*/

void Editor::Load()
{ 
	object = Model::Load("..\\..\\resources\\models\\woman\\PillarWoman.fbx");
	object->GetComponent<Transform>().lock()->SetRotation((glm::radians(glm::vec3(-90, -90, 0))));
	auto cameraPtr = camera.AddComponent<Camera>();
	camera.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0,1.5f,1));
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

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_Q)) {
		object->GetComponent<Transform>().lock()->Rotate(glm::vec3(0, 0, -camSpeed * deltaTime));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_E)) {
		object->GetComponent<Transform>().lock()->Rotate(glm::vec3(0, 0, camSpeed * deltaTime));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, 0, -camSpeed * deltaTime));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_LEFT_CONTROL)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, 0, camSpeed * deltaTime));
	}

	object->Tick(deltaTime);
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

	auto camComponent = camera.GetComponent<Camera>().lock();
	auto modelTransform = object->GetComponent<Transform>().lock();
	auto camTransform = camera.GetComponent<Transform>().lock();

	std::queue<GameObject*> renderQueue;
	renderQueue.push(modelTransform->gameObject);

	while (renderQueue.size() != 0) 
	{
		GameObject* obj = renderQueue.front();
		renderQueue.pop();
		auto mesh = obj->GetComponent<Mesh>();
		if (mesh.lock()) {
			mesh.lock()->Draw(*camComponent, *camTransform, *modelTransform);
		}

		auto children = obj->GetComponent<Transform>().lock()->GetChildren();
		for (auto child : children) 
		{
			renderQueue.push(child->gameObject);
		}
	}
	
}

void Editor::Unload()
{

}