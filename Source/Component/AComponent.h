#pragma once
#include <memory>

class GameObject;

class AComponent
{
	friend class GameObject;

protected:
	virtual void Tick(float deltaTime) = 0;
	std::shared_ptr<GameObject> owner;

public:
	AComponent();
	virtual ~AComponent();
};

