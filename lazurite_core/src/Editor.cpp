#include "Editor.h"
#include "subsystem/Input.h"
#include <iostream>

void Editor::Load()
{ 
	/*
	auto modelPtr = testObj.AddComponent<Model>();
	modelPtr.lock()->LoadModel("resources/models/Anj1.obj");
	testObj.GetComponent<Transform>().lock()->SetScale(glm::vec3(.1f, .1f, .1f));

	shaderProgram = new ShaderProgram();
	shaderProgram->CompileShader("resources/shaders/BlinnPhongVert.glsl", OpenGLShader::VERTEX);
	shaderProgram->CompileShader("resources/shaders/BlinnPhongFrag.glsl", OpenGLShader::FRAGMENT);
	shaderProgram->Link();
	shaderProgram->Validate();
	*/
}

void Editor::Tick(float deltaTime)
{

}

void Editor::Draw(float deltaTime)
{
	// testObj.GetComponent<Model>().lock()->Draw(*shaderProgram);
}

void Editor::Unload()
{
	// delete shaderProgram;
}