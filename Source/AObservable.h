#pragma once
#include "IObserver.h"
#include <list>

class AObservable
{
public:
	virtual ~AObservable();

	void AddObserver(IObserver* observer);
	void RemoveObserver(IObserver* observer);

protected:
	void Notify(const GameObject& go, void* data);

private:
	std::list<IObserver*> observers;
};

