#include "GameObject.h"
#include "Component/AComponent.h"
#include <type_traits>

GameObject::GameObject()
{
	// We intialize all objects with a transform component.
	_components.insert(std::pair<ComponentID, StrongComponentPtr>(typeid(Transform), std::make_shared<Transform>()));
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

Transform & GameObject::GetTransform()
{
	return GetTransform();
}

void GameObject::Tick(float deltaTime)
{
	if (!_isTicking) return;

	for (const auto& component : _components)
	{
		if(component.second != nullptr && component.second.get()->IsActive())
			component.second.get()->Tick(deltaTime);
	}
}

template<class T>
void GameObject::AddComponent()
{
	_components.insert(std::pair<ComponentID, StrongComponentPtr>(typeid(T), std::make_shared<T>()));
}

template<class T>
void GameObject::RemoveComponent()
{
	auto it = _components.find(typeid(T));
	if(it != _components.end())
		_components.erase(it);
}

template<class T>
std::weak_ptr<T> GameObject::GetComponent() const
{
	auto it = _components.find(typeid(T));
	if (it != _components.end())
		_components.erase(it);
}