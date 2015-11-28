#pragma once
#include <memory>

class AComponent
{
	friend class GameObject;
public:
	AComponent();
	virtual ~AComponent();

	GameObject* owner;
protected:
	virtual void update(float deltaTime) = 0;

private:
};

