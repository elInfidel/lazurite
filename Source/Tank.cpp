// ---------------------------------------------------------------------------
// Tank.h
// The tank object for marking game
//
// Original author: <Liam Parker>
// Date created: 02/01/2015
// ---------------------------------------------------------------------------
#include "Tank.h"
#include "GL/glfw3.h"

Tank::Tank()
{
	width = 0;
	height = 0;
	bpp = 0;
	movementSpeed = 0.0f;

	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	facing = Facing::UP;

	rotation.z = 0.0f;

	base.SetTexture("./Content/tank_moving_1.png", width, height, bpp);
}

Tank::~Tank()
{
	
}

Tank::Tank(float posX, float posY)
{
	width = 0;
	height = 0;
	bpp = 0;
	movementSpeed = 300.0f;

	facing = Facing::UP;

	position.x = posX;
	position.y = posY;

	base.SetTexture("./Content/tank_moving_1.png", width, height, bpp);
}

void Tank::Update()
{
	//Moving tank
	base.transform.Translate(position);
	//Moving and rotating turret with tank
	turret.transform.Translate(position);
	turret.transform.Rotate(rotation);
}

void Tank::Draw()
{
	turret.Draw();

	base.Draw();
}
