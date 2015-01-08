// ---------------------------------------------------------------------------
// Projectile.h
// Missiles fired by tanks
//
// Original author: <Liam Parker>
// Date created: 05/01/2015
// ---------------------------------------------------------------------------
#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "Engine/Sprite.h"
#include "Actor.h"

enum Source
{
	PLAYER,
	ENEMY
};

using namespace lazurite;

class Projectile : public Actor
{
public:
	// Instatiates a projectile at 0,0 with no rotation
	Projectile();
	~Projectile();
	// Instantiates a projectile at position with degrees rotation
	Projectile(float posX, float posY, float degRot, Source newShooter);

	inline Source getShooter() { return source; }
	void Update();
	void Draw();

private:
	// Speed of projectiles
	float speed;

	// Movement related variables
	float scaleX, scaleY;
	float velX, velY;

	// The source of the projectile
	Source source;

	// The sprite for the projectile
	Sprite sprite;
};

#endif // _PROJECTILE_H_