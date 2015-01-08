// ---------------------------------------------------------------------------
// Player.h
// An extension for the tank object encapsulating movement functionality
//
// Original author: <Liam Parker>
// Date created: 05/01/2015
// ---------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Tank.h"

class Player : public Tank
{
public:
	Player();
	~Player();

	Player(float posX, float posY);

	virtual void Update();
};

#endif // _PLAYER_H_