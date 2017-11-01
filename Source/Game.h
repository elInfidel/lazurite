#pragma once
#include "Engine.h"
#include "Component/Model.h"
#include "Component/Transform.h"
#include "ParticleEmitter.h"
#include "GameObject.h"
#include "Cubemap.h"
#include <memory>

class FlyCamera;

class Game : public Engine
{
protected:
	virtual void Load();
	virtual void Tick(float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Unload();

	GameObject obj;
	std::weak_ptr<Transform> transform;

	// Tweak bar vars
	float fps = 0.0f;
	vec3 lightPos = vec3(0.0f, 100.0f, 0.0f);

	vec3 matA = vec3(0.1, 0.1, 0.15);
	vec3 matD = vec3(0, 0.5, 0.9);
	vec3 matS = vec3(0.6, 0.45, 1);
	float specularPower = 45;
	vec3 rimCol = vec3(0.5, 0.5, 0.8);
	float rimPow = 7;
};

