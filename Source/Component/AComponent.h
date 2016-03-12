#pragma once
#include <memory>

class AComponent
{
	friend class GameObject;
public:
	AComponent();
	virtual ~AComponent();

	shared_ptr<GameObject> owner;
protected:
	virtual void Update(float deltaTime) = 0;
};

