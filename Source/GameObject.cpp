#include "GameObject.h"
#include "Component/AComponent.h"
#include <type_traits>

GameObject::GameObject()
{
	// We intialize all objects with a transform component.
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	_components.clear();
}

void GameObject::SetActive(bool active)
{
	_isActive = active;
}

bool GameObject::IsActive() const
{
	return _isActive;
}

void GameObject::SetTick(bool tick)
{
	_isTicking = tick;
}

bool GameObject::IsTicking() const
{
	return _isTicking;
}

void GameObject::Tick(float deltaTime)
{
	for (const auto& component : _components)
	{
		if(component.second != nullptr && component.second.get()->IsActive())
			component.second.get()->Tick(deltaTime);
	}
}