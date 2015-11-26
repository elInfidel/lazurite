#pragma once
#include "Component/AComponent.h"
#include <vector>

using namespace std;

class GameObject
{
public:
	void AddComponent(AComponent* newComponent);

	template<class T> void RemoveComponent(T remove);
	template<class T> T* GetComponent(T get);

protected:
	GameObject();
	virtual ~GameObject();

	vector<AComponent*> components;

	virtual void Update(float deltaTime);
};

