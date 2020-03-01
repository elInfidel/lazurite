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
	modelPtr.lock()->LoadModel("resources\\models\\woman\\PillarWoman.obj");
	testObj.GetComponent<Transform>().lock()->SetRotation((glm::radians(glm::vec3(0, -90, 0))));
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

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, 0, -camSpeed * deltaTime));
	}

	if (Input::GetInstance()->GetKeyDown(GLFW_KEY_LEFT_CONTROL)) {
		camera.GetComponent<Transform>().lock()->Translate(glm::vec3(0, 0, camSpeed * deltaTime));
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