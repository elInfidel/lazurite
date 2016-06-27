#pragma once
#include "Component/Transform.h"

#include <vector>

using namespace std;

class AComponent;

class GameObject
{
	friend class Scene;
public:
	GameObject();
	virtual ~GameObject();

	void SetActive(bool active);
	bool IsActive();

	// Components
	template<class T> void AddComponent();
	template<class T> void RemoveComponent();
	template<class T> T* GetComponent();

protected:
	vector<AComponent*> _components;

	virtual void Update(float deltaTime);
private:
	bool _isActive = true;;
};

