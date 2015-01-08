// ---------------------------------------------------------------------------
// Enemy.cpp
// An extension for the tank object encapsulating enemy ai functionality
//
// Original author: <Liam Parker>
// Date created: 05/01/2015
// ---------------------------------------------------------------------------
#include "Enemy.h"
#include "Engine/Time.h"
#include "Math/MathF.h"
#include "Math/Vector3.h"
#include "Game.h"

Enemy::Enemy()
{
	timer = 0.0f;
}

Enemy::~Enemy()
{

}

Enemy::Enemy(float posX, float posY, Actor* target) : Tank(posX, posY)
{
	this->target = target;
	turret.SetTexture("./Content/turret_red.png", width, height, bpp);
	fireRate = 2.0f;
	timer = 0.0f;
}

void Enemy::Update()
{
	timer += Time::GetDeltaTime();

	if(target != nullptr)
	{
		Vector3 targetPos = target->GetPosition();
		float deltaX = targetPos.x - position.x;
		float deltaY = targetPos.y - position.y;

		float angle = atan2f(-deltaY , -deltaX) * (180 / (float)PI) + 90;

		rotation.z -= angle;
		turret.transform.Rotate(rotation);
		rotation.z = angle;

		if(timer > fireRate)
		{
			Game::CreateProjectile(position, rotation.z, Source::ENEMY);
			timer = 0.0f;
		}
	}

	base.transform.Translate(position);
	turret.transform.Translate(position);
	turret.transform.Rotate(rotation);
}