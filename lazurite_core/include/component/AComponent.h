#pragma once
#include <memory>

class GameObject;

class AComponent
{
	friend class GameObject;
	bool _isActive = true;

protected:
	virtual void Tick(float deltaTime) = 0;
	GameObject* gameObject;

public:
	AComponent();
	virtual ~AComponent();

	bool IsActive();

};

