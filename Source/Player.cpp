// ---------------------------------------------------------------------------
// Player.cpp
// An extension for the tank object encapsulating movement functionality
//
// Original author: <Liam Parker>
// Date created: 05/01/2015
// ---------------------------------------------------------------------------
#include "Player.h"
#include "Engine/Time.h"
#include "Game.h"
Player::Player() : Tank(0.0f, 0.0f)
{
	fireRate = 1.0f;
	rotationSpeed = 0.0f;
}


Player::~Player()
{

}

Player::Player(float posX, float posY) : Tank(posX, posY)
{
	turret.SetTexture("./Content/turret_blue.png", width, height, bpp);
	fireRate = 0.5f;
	rotationSpeed = 150.0f;
}

void Player::Update()
{
	static float timer;
	timer += Time::GetDeltaTime();

	// WASD movement
	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
	{
		position.y += movementSpeed * Time::GetDeltaTime();
		facing = Facing::UP;
	}
	else if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x += -movementSpeed * Time::GetDeltaTime();
		facing = Facing::RIGHT;
	}
	else if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
	{
		position.y += -movementSpeed * Time::GetDeltaTime();
		facing = Facing::UP;
	}
	else if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x += movementSpeed * Time::GetDeltaTime();
		facing = Facing::RIGHT;
	}

	// QE rotation
	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Q) == GLFW_PRESS)
		rotation.z += rotationSpeed * Time::GetDeltaTime();
	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
		rotation.z += -rotationSpeed * Time::GetDeltaTime();

	// Fire Projectile
	if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS && timer > fireRate)
	{
		Game::CreateProjectile(position, rotation.z, Source::PLAYER);
		timer = 0.0f;
	}

	// Moving tank
	base.transform.Translate(position);
	if(facing == Facing::UP)
		base.transform.Rotate(Vector3(0.0f, 0.0f, 0.0f));
	if(facing == Facing::UP)
		base.transform.Rotate(Vector3(0.0f, 0.0f, 0.0f));
	if(facing == Facing::RIGHT)
		base.transform.Rotate(Vector3(0.0f, 0.0f, 90.0f));
	if(facing == Facing::RIGHT)
		base.transform.Rotate(Vector3(0.0f, 0.0f, 90.0f));

	// Moving and rotating turret with tank
	turret.transform.Translate(position);
	turret.transform.Rotate(rotation);
}