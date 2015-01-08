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
#include "Actor.h"
#include "Projectile.h"
#include "Math/Vector3.h"
#include <vector>

using namespace lazmath;

class Game : public lazurite::Application
{
public:
	Game();
	virtual ~Game();

	virtual bool Load();

	static void CreateProjectile(Vector3 position, float degRot, Source shooter);

	virtual void Update();
	virtual void Render();

	virtual void Unload();

private:
	Actor* tanks[4];
	std::vector<Actor*> actors;
	static std::vector<Projectile*> projectiles;

	static int screenWidth;
	static int screenHeight;
};

#endif // _GAME_H_
