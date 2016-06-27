#pragma once
#include "CoreSystem.h"

class Physics : public CoreSystem
{
public:
	Physics();
	~Physics();

	void Initialize();
	void InitializeDebugger();
	void Update(float deltaTime);

	void Shutdown();

private:
};