#include "Editor.h"
#include "Subsystem/Input.h"
#include <iostream>

void Editor::Load()
{ 
	auto modelPtr = testObj.AddComponent<Model>();
	modelPtr.lock()->LoadModel("Resources/Models/bunny.obj");

	shaderProgram = new ShaderProgram();
	shaderProgram->CompileShader("Resources/Shaders/BlinnPhongVert.glsl", OpenGLShader::VERTEX);
	shaderProgram->CompileShader("Resources/Shaders/BlinnPhongFrag.glsl", OpenGLShader::FRAGMENT);
	shaderProgram->Link();
	shaderProgram->Validate();
}

void Editor::Tick(float deltaTime)
{

}

void Editor::Draw(float deltaTime)
{
	testObj.GetComponent<Model>().lock()->Draw(*shaderProgram);
}

void Editor::Unload()
{
	delete shaderProgram;
}