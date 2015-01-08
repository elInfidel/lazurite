// ---------------------------------------------------------------------------
// Enemy.h
// An extension for the tank object encapsulating enemy ai functionality
//
// Original author: <Liam Parker>
// Date created: 05/01/2015
// ---------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Tank.h"
#include "Actor.h"

class Enemy : public Tank
{
public:
	Enemy();
	~Enemy();

	Enemy(float posX, float posY, Actor* target);

	virtual void Update();
private:
	Actor* target;
	float timer;
};

#endif // _ENEMY_H_