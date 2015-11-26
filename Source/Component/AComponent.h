#pragma once

class AComponent
{
	friend class GameObject;

public:
	AComponent();
	virtual ~AComponent();

protected:
	virtual void update(float deltaTime);
};

