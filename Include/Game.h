// ---------------------------------------------------------------------------
// Game.h
// The base for TinyTanks to be run off of the engine.
//
// Original author: <Liam Parker>
// Date Created: 10/11/2014
// ---------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "Engine/Application.h"

class Game : public lazurite::Application
{
public:
	Game();
	virtual ~Game();

	virtual bool Load();

	virtual void Update();
	virtual void Draw();

	virtual void Unload();
};

#endif // _GAME_H_
