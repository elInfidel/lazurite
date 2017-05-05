#include "Game.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "FlyCamera.h"
#include "glm/gtc/type_ptr.hpp"
#include "Core/Input.h"
#include "GameObject.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

void Game::Load()
{
	// Initialize camera
	camera = new FlyCamera();
	camera->SetPerspective(70.0f, 16.0f / 9.0f, 1.0f, 100.0f);
	camera->transform.SetTranslation(vec3(0,0,4));
}

void Game::Update(float deltaTime)
{
	camera->Update(deltaTime);
}

void Game::Draw(float deltaTime)
{

}

void Game::Unload()
{
	delete camera;
}