// ---------------------------------------------------------------------------
// Game.cpp
// The base for TinyTanks to be run off of the engine.
//
// Original author: <Liam Parker>
// Date Created: 10/11/2014
// ---------------------------------------------------------------------------
#include "Game.h"
#include "Engine/Application.h"
#include "Tank.h"
#include "Player.h"
#include "Enemy.h"
using namespace lazurite;

std::vector<Projectile*> Game::projectiles;
int Game::screenWidth = 1920;
int Game::screenHeight = 1080;

Game::Game()
{
	
}

bool Game::Load()
{
	bool loadComplete = false; 

	loadComplete = LazuriteInit(screenWidth, screenHeight, "Lazurite Engine", false);

	if(loadComplete)
	{
		glfwSetWindowSize(glfwGetCurrentContext(), screenWidth, screenHeight);

		tanks[0] = new Player((float)screenWidth/2, (float)screenHeight/3);
		tanks[1] = new Enemy((float)screenWidth/2 - 200, (float)screenHeight - 100, tanks[0]);
		tanks[2] = new Enemy((float)screenWidth/2, (float)screenHeight - 100, tanks[0]);
		tanks[3] = new Enemy((float)screenWidth/2 + 200, (float)screenHeight - 100, tanks[0]);

		for(int i = 0; i < 4; ++i)
		{
			actors.push_back(tanks[i]);
		}
		return true;
	}
	else
		return false;
}

void Game::CreateProjectile(Vector3 position, float degRot, Source shooter)
{
	projectiles.push_back(new Projectile(position.x, position.y, degRot, shooter));
}

void Game::Update()
{
	for(size_t i = 0; i < actors.size(); ++i)
	{
		actors[i]->Update();
	}

	for(size_t i = 0; i < projectiles.size(); ++i)
	{
		projectiles[i]->Update();
	}
}

void Game::Render()
{
	for(size_t i = 0; i < actors.size(); ++i)
	{
		actors[i]->Draw();
	}

	for(size_t i = 0; i < projectiles.size(); ++i)
	{
		projectiles[i]->Draw();
	}
}

void Game::Unload()
{
	for(size_t i = 0; i < actors.size(); ++i)
	{
		delete actors[i];
	}

	for(size_t i = 0; i < projectiles.size(); ++i)
	{
		delete projectiles[i];
	}

	LazuriteTerminate();
}

Game::~Game()
{

}

/////////////////////////////////////////
//
// PROGRAM ENTRY POINT
//
/////////////////////////////////////////
int main(int argc,char *argv[])
{
	Game *game = new Game();

	if(game->Load() == false)
		return -1;
	game->Run();
	game->Unload();

	delete game;

	return 0;
}
