#include "Editor.h"
#include "subsystem/Input.h"
#include <iostream>

void Editor::Load()
{ 
	auto modelPtr = testObj.AddComponent<Model>();
	modelPtr.lock()->LoadModel("resources/models/PillarWoman_HalfNude.fbx");
	testObj.GetComponent<Transform>().lock()->SetScale(glm::vec3(.1f, .1f, .1f));
	testObj.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0, -16, -8));
	testObj.GetComponent<Transform>().lock()->SetRotation((glm::radians(glm::vec3(90, 0, 180))));

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
	auto camTransform = camera.GetComponent<Transform>().lock();
	testObj.GetComponent<Model>().lock()->Draw(*camComponent, *camTransform, *modelTransform);
}

void Editor::Unload()
{
}