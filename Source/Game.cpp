// ---------------------------------------------------------------------------
// Game.cpp
// The base for TinyTanks to be run off of the engine.
//
// Original author: <Liam Parker>
// Date Created: 10/11/2014
// ---------------------------------------------------------------------------
#include "Game.h"
#include "Engine/Application.h"
#include "Engine/Sprite.h"

using namespace lazurite;

Game::Game()
{
	
}

bool Game::Load()
{
	return LazuriteInit(1024, 768, "Lazurite Engine", false);
}

void Game::Update()
{
	
}

void Game::Draw()
{
	
}

void Game::Unload()
{
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
