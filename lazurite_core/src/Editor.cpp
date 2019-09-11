#include "Editor.h"
#include "subsystem/Input.h"
#include <iostream>

void Editor::Load()
{ 
	auto modelPtr = testObj.AddComponent<Model>();
	modelPtr.lock()->LoadModel("resources/models/Anj1.obj");
	testObj.GetComponent<Transform>().lock()->SetScale(glm::vec3(.2f, .2f, .2f));
	testObj.GetComponent<Transform>().lock()->SetPosition(glm::vec3(0, 0, -5));

	auto cameraPtr = camera.AddComponent<Camera>();

	shaderProgram = new ShaderProgram();
	shaderProgram->CompileShader("resources/shaders/BlinnPhongVert.glsl", OpenGLShader::VERTEX);
	shaderProgram->CompileShader("resources/shaders/BlinnPhongFrag.glsl", OpenGLShader::FRAGMENT);
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

	shaderProgram->Use();
	shaderProgram->SetUniform("vpMat", camComponent->GetProjectionMatrix() * camComponent->GetViewMatrix() );
	shaderProgram->SetUniform("mvMat", camComponent->GetViewMatrix() * modelTransform->GetWorldMatrix());
	shaderProgram->SetUniform("pMat", camComponent->GetProjectionMatrix());
	shaderProgram->SetUniform("vMat", camComponent->GetViewMatrix());
	shaderProgram->SetUniform("mvpMat", camComponent->GetProjectionMatrix() * camComponent->GetViewMatrix() * modelTransform->GetWorldMatrix());
	shaderProgram->SetUniform("lightPos", vec3(0.0, 0.5, -3.0));

	testObj.GetComponent<Model>().lock()->Draw(*shaderProgram);
}

void Editor::Unload()
{
	delete shaderProgram;
}