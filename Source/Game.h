#pragma once
#include "Application.h"
#include "Model.h"
#include "ProceduralMesh.h"
#include "Plane.h"
#include "tweakbar/AntTweakBar.h"
#include "ParticleEmitter.h"

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

	Model* model;
	ShaderProgram* modelMat;
	ShaderProgram* partMat;

	// Tweak bar vars
	float fps = 0.0f;
	vec3 lightDir;

};

