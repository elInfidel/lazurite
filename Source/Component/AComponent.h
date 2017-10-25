#pragma once
#include <memory>

class GameObject;

class AComponent
{
	friend class GameObject;

protected:
	virtual void Update(float deltaTime) = 0;
public:
	AComponent();
	virtual ~AComponent();

	std::shared_ptr<GameObject> owner;
};

