// ---------------------------------------------------------------------------
// Game.h
// The base for TinyTanks to be run off of the engine.
//
// Original author: <Liam Parker>
// ---------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#include "Engine/Application.h"

class Game : public Application
{
public:
	Game();
	virtual ~Game();

	virtual bool Load();
	virtual void Unload();

	virtual void Update();
	virtual void Draw();
};

#endif // _GAME_H_
