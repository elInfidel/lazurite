//Testing entry point
#include "Engine/Application.h"
#include "Engine/Sprite.h"
#include "GL/glew.h"
#include "GL/glfw3.h"
#include "GLM/vec3.hpp"
#include <iostream>

using namespace lazurite;
using glm::vec3;

class Program : public Application
{
public:
	Program();
	~Program();

	virtual bool Load();
	virtual void Unload();

	virtual void Update();
	virtual void Render();

private:
	vec3 pos;
	int width, height, bpp;
	Sprite* sprite;
};

Program::Program()
{

}

Program::~Program()
{

}

bool Program::Load()
{
	 LazuriteInit(1024, 768, "Lazurite Engine", false);
	 sprite = new Sprite();
	 sprite->SetTexture("Content/test_texture.png", width, height, bpp);
	 return true;
}

void Program::Unload()
{
	delete sprite;
	LazuriteTerminate();
}

void Program::Update()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		sprite->transform.Translate(vec3(0.0f, 5.0f, 0.0f));
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		sprite->transform.Translate(vec3(-5.0f, 0.0f, 0.0f));
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		sprite->transform.Translate(vec3(0.0f, -5.0f, 0.0f));
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		sprite->transform.Translate(vec3(5.0f, 0.0f, 0.0f));
}

void Program::Render()
{
	sprite->Draw();
}

int main()
{
	Program* program = new Program();

	if (program->Load() == false)
		return -1;
	program->Run();
	program->Unload();

	delete program;

	return 0;
}