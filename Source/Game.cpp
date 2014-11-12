// ---------------------------------------------------------------------------
// Game.cpp
// The base for TinyTanks to be run off of the engine.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#include "Game.h"
#include "Engine/Application.h"

/////////////////////////////////////////
//
// CONSTRUCTORS
//
/////////////////////////////////////////
Game::Game()
{
}

/////////////////////////////////////////
//
// MEMBER FUNCTIONS
//
/////////////////////////////////////////
bool Game::Load()
{
	return Initialize(1024, 768, "Lazurite Engine", false);
}

void Game::Unload()
{
	LazuriteTerminate();
}

void Game::Update()
{

}

void Game::Draw()
{
	ClearScreen();

}

/////////////////////////////////////////
//
// DESTRUCTORS
//
/////////////////////////////////////////
Game::~Game()
{
}

/////////////////////////////////////////
//
// PROGRAM ENTRY POINT
//
/////////////////////////////////////////
int main()
{
	Game *game = new Game();

	if(game->Load() == false)
		return -1;
	game->Run();
	game->Unload();

	delete game;

	return 0;
}