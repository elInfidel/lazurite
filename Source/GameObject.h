#pragma once
#include "Component/AComponent.h"
#include "Component/Transform.h"

#include <vector>

using namespace std;

class GameObject
{
	friend class Scene;
public:
	GameObject();
	virtual ~GameObject();

	Transform GetTransform();

	// Components
	void AddComponent(AComponent* newComponent);
	template<class T> void RemoveComponent(T remove);
	template<class T> T* GetComponent(T get);

protected:
	Transform transform;

	vector<AComponent*> components;

	virtual void Update(float deltaTime);
};

