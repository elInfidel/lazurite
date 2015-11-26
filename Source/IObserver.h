#pragma once
#include "GameObject.h"

class IObserver
{
public:
	virtual void Notify(const GameObject& go, void* data) = 0;
};

