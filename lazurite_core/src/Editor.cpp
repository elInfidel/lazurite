#include "Editor.h"
#include "subsystem/Input.h"
#include <iostream>

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
	auto modelPtr = testObj.AddComponent<Model>();
	modelPtr.lock()->LoadModel("resources\\models\\PillarWoman.fbx");
	testObj.GetComponent<Transform>().lock()->SetScale(glm::vec3(.1f));
	testObj.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0, -15, 0));
	testObj.GetComponent<Transform>().lock()->SetRotation((glm::radians(glm::vec3(90, 180, 180))));

	auto cameraPtr = camera.AddComponent<Camera>();
	camera.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0,0,10));
}

void Editor::Tick(float deltaTime)
{
	camera.GetComponent<Camera>().lock()->Tick(deltaTime);

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_W)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, 1 * deltaTime, 0));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_A)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(-1 * deltaTime, 0, 0));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_S)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, -1 * deltaTime, 0));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_D)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(1 * deltaTime, 0, 0));
	}
}

void Editor::Draw(float deltaTime)
{
	auto camComponent = camera.GetComponent<Camera>().lock();
	auto modelTransform = testObj.GetComponent<Transform>().lock();
	auto camTransform = camera.GetComponent<Transform>().lock();
	testObj.GetComponent<Model>().lock()->Draw(*camComponent, *camTransform, *modelTransform);
}

void Editor::Unload()
{
}