// ---------------------------------------------------------------------------
// Tank.h
// The tank object for marking game
//
// Original author: <Liam Parker>
// Date created: 02/01/2015
// ---------------------------------------------------------------------------
#ifndef _TANK_H_
#define _TANK_H_
#include "Engine/Sprite.h"
#include "Actor.h"
using namespace lazmath;
using namespace lazurite;

enum Facing
{
	RIGHT,
	UP
};

class Tank : public Actor
{
public:
	Tank();
	~Tank();

	Tank(float posX, float posY);

	virtual void Update();
	virtual void Draw();

protected:
	Sprite base;
	Sprite turret;

	Facing facing;
	float movementSpeed;
	float fireRate;
	float rotationSpeed;
};

#endif // _TANK_H_