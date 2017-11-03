#pragma once
#include "Engine.h"
#include "Component/Model.h"
#include "Component/Transform.h"
#include "GameObject.h"

#include <memory>

class Game : public Engine
{
protected:
	virtual void Load();
	virtual void Tick(float deltaTime);
	virtual void Draw(float deltaTime);
	virtual void Unload();

	GameObject obj;

	bool developerMenu = false;
};