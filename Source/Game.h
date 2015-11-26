#pragma once
#include "Application.h"
#include "Model.h"
#include "tweakbar/AntTweakBar.h"
#include "ParticleEmitter.h"
#include "Cubemap.h"

class FlyCamera;

class Game : public Application
{
protected:
	virtual void Load();
	virtual void Update(float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Unload();

	FlyCamera* camera;
	TwBar* bar;

	ShaderProgram* modelShader;
	Model* model;

	// Tweak bar vars
	float fps = 0.0f;
	vec3 lightDir;

	vec3 matA = vec3(10.0f);
	vec3 matD = vec3(0.0f, 50.0f, 200.0f);
	vec3 matS = vec3(255.0f);
	float specularPower = 280.0f;
};

