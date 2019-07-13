#pragma once
#include <memory>

class GameObject;

class AComponent
{
	friend class GameObject;
	bool _isActive = true;

protected:
	virtual void Tick(float deltaTime) = 0;
	std::shared_ptr<GameObject> gameObject;

public:
	AComponent();
	virtual ~AComponent();

	bool IsActive();

};

