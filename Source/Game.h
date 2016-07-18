#pragma once
#include "Engine.h"
#include "Component/Model.h"
#include "ParticleEmitter.h"
#include "Cubemap.h"

class FlyCamera;

class Game : public Engine
{
protected:
	virtual void Load();
	virtual void Update(const Scene& scene, float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Unload();

	FlyCamera* camera;

	ShaderProgram* modelShader;
	Model* model;

	// Tweak bar vars
	float fps = 0.0f;
	vec3 lightDir = vec3(0.0f, -1.0f, 0.0f);

	vec3 matA = vec3(0.4f, 0.4f, 0.7f);
	vec3 matD = vec3(1.0f, 1.0f, 1.0f);
	vec3 matS = vec3(1.0f, 1.0f, 1.0f);
	float specularPower = 15;
	vec3 rimCol = vec3(1.0f, 1.0f, 1.0f);
	float rimPow = 128.f;
};

