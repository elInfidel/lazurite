//Testing entry point
#include "Engine/Application.h"
#include "Engine/Sprite.h"
#include "GL/glew.h"
#include "GL/glfw3.h"
#include "GLM/vec3.hpp"
#include <iostream>
#include "Engine/Camera.h"

using namespace lazurite;
using glm::vec3;

class Program : public Application
{
public:
	Program();
	~Program();

	virtual void Update();
	virtual void Render();

private:
	vec3 pos;
	int width, height, bpp;
	Sprite* sprite;
	Camera* cam;
};

Program::Program()
{
	if (LazuriteInit(1024, 768, "Lazurite Engine", false))
	{
		sprite = new Sprite();
		cam = new Camera();
		cam->SetOrtho(0, 1024, 0, 768, 0.0f, 100.0f);
		sprite->SetTexture("Content/test_texture.png", width, height, bpp);
	}
}

Program::~Program()
{
	delete sprite;
	LazuriteTerminate();
}

void Program::Update()
{
	if (Input::GetKey(GLFW_KEY_W) == true)
		sprite->transform.Translate(vec3(0.0f, 50.0f, 0.0f));
	if (Input::GetKey(GLFW_KEY_A) == true)
		sprite->transform.Translate(vec3(-50.0f, 0.0f, 0.0f));
	if (Input::GetKey(GLFW_KEY_S) == true)
		sprite->transform.Translate(vec3(0.0f, -50.0f, 0.0f));
	if (Input::GetKey(GLFW_KEY_D) == true)
		sprite->transform.Translate(vec3(50.0f, 0.0f, 0.0f));

}

void Program::Render()
{
	sprite->Draw(cam);
}

int main()
{
	Program* program = new Program();

	program->Run();

	delete program;

	return 0;
}