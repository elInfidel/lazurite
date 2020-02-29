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

	shaderProgram = new ShaderProgram();
	shaderProgram->CompileShader("resources/shaders/PBRVert.glsl", OpenGLShader::VERTEX);
	shaderProgram->CompileShader("resources/shaders/PBRFrag.glsl", OpenGLShader::FRAGMENT);
	shaderProgram->Link();
	shaderProgram->Validate();
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

	shaderProgram->Use();

	shaderProgram->SetUniform("model", modelTransform->GetWorldMatrix());
	shaderProgram->SetUniform("view", camComponent->GetViewMatrix());
	shaderProgram->SetUniform("projection", camComponent->GetProjectionMatrix());

	vector<vec3> pointPositions = {
		vec3(-3.5, 4.0, -4.0),
		vec3(0.0, 4.0, -4.0),
		vec3(3.5, 4.0, -4.0),
		vec3(-3.5, 4.0, 0.0),
	};

	vector<vec3> pointColors = {
		vec3(255, 255, 255),
		vec3(255, 255, 255),
		vec3(255, 255, 255),
		vec3(255, 255, 255),
	};

	shaderProgram->SetUniform("lightPositions", pointPositions);
	shaderProgram->SetUniform("lightColors", pointColors);
	shaderProgram->SetUniform("camPos", camTransform->GetPosition());

	testObj.GetComponent<Model>().lock()->Draw(*shaderProgram);
}

void Editor::Unload()
{
}