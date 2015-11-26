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

	vec3 matA;
	vec3 matD;
	vec3 matS;
	float specularPower;
	vec3 rimCol;
	float rimPow;
};

