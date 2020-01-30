#include "Editor.h"
#include "subsystem/Input.h"
#include <iostream>

void Editor::Load()
{ 
	auto modelPtr = testObj.AddComponent<Model>();
	testObj.GetComponent<Transform>().lock()->SetScale(glm::vec3(5.f, 5.f, 5.f));
	testObj.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0, -.5f, -2.f));
	modelPtr.lock()->LoadModel("./models/bunny.obj");

	auto cameraPtr = camera.AddComponent<Camera>();
	camera.GetComponent<Transform>().lock()->SetPosition(vec3(0, 0, -10));
}

void Editor::Tick(float deltaTime)
{
	camera.GetComponent<Camera>().lock()->Tick(deltaTime);
}

void Editor::Draw(float deltaTime)
{
	auto transform = testObj.GetComponent<Transform>().lock();
	auto cam = camera.GetComponent<Camera>().lock();
	testObj.GetComponent<Model>().lock()->Draw(
		cam->GetViewMatrix(),
		cam->GetProjectionMatrix(),
		transform->GetWorldMatrix()
	);
}

void Editor::Unload()
{
}