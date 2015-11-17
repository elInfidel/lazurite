#pragma once
#include "Component/AComponent.h"
#include <vector>

using namespace std;

class GameObject
{
public:
	void AddComponent(AComponent* newComponent);

protected:
	GameObject();
	virtual ~GameObject();

	vector<AComponent*> components;

	virtual void Update();
};

