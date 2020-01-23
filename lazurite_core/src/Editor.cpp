#include "Editor.h"
#include "subsystem/Input.h"
#include <iostream>

void Editor::Load()
{ 
	auto modelPtr = testObj.AddComponent<Model>();
	modelPtr.lock()->LoadModel("./models/bunny.obj");
	testObj.GetComponent<Transform>().lock()->SetScale(glm::vec3(5.f, 5.f, 5.f));
	testObj.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0, -.5f, -2.f));

	auto cameraPtr = camera.AddComponent<Camera>();

}

void Editor::Tick(float deltaTime)
{
	camera.GetComponent<Camera>().lock()->Tick(deltaTime);
}

void Editor::Draw(float deltaTime)
{
	auto camComponent = camera.GetComponent<Camera>().lock();
	auto modelTransform = testObj.GetComponent<Transform>().lock();
}

void Editor::Unload()
{
}