// ---------------------------------------------------------------------------
// Projectile.cpp
// Missiles fired by tanks
//
// Original author: <Liam Parker>
// Date created: 05/01/2015
// ---------------------------------------------------------------------------
#include "Projectile.h"
#include "Engine/Time.h"
#include "Math/MathF.h"

Projectile::Projectile()
{
	speed = 0.0f;
	position.x = 0.0f;
	position.y = 0.0f;

	scaleX = 0;
	scaleY = 0;
	velX = 0;
	velY = 0;

	//Uniformly scaling the sporite to make it smaller
	sprite.transform.Scale(0.2f, 0.2f, 0.2f);
}


Projectile::~Projectile()
{

}

Projectile::Projectile(float posX, float posY, float degRot, Source newShooter)
{
	speed = 20.0f;
	position.x = posX;
	position.y = posY;

	rotation.z = degRot;
	source = newShooter;

	// Figuring out directional information for projectile
	// Here we add 90 to the rotation amount to line the projectiles up with the cannon
	degRot += 90;
	scaleX = cos(DegToRad(degRot));
	scaleY = sin(DegToRad(degRot));

	velX = (speed * scaleX);
	velY = (speed * scaleY);

	//Uniformly scaling the sporite to make it smaller
	sprite.transform.Scale(0.2f, 0.2f, 0.2f);

	sprite.transform.Translate(Vector3(position.x, position.y, position.z));

	sprite.SetTexture("./Content/projectile.png", width, height, bpp);
}

void Projectile::Update()
{
	sprite.transform.Translate(position);

	//Sending projectile in its instantiated direction at given speed.
	position.x += velX * (speed * Time::GetDeltaTime());
	position.y += velY * (speed * Time::GetDeltaTime());

	sprite.transform.Rotate(rotation);
}

void Projectile::Draw()
{
	sprite.Draw();
}