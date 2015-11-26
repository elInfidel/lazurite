#include "AObservable.h"

AObservable::~AObservable()
{
	observers.clear();
}

void AObservable::AddObserver(IObserver* observer)
{
	observers.push_back(observer);
}

void AObservable::RemoveObserver(IObserver* observer)
{
	for (std::list<IObserver*>::const_iterator itr = observers.begin(), end = observers.end(); itr != end; ++itr)
	{
		if (*itr == observer)
		{
			observers.erase(itr);
			return;
		}
	}
}

void AObservable::Notify(const GameObject& go, void* data)
{
	for (std::list<IObserver*>::const_iterator itr = observers.begin(), end = observers.end(); itr != end; ++itr)
	{
		(*itr)->Notify(go, data);
	}
}