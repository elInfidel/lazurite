#include "GameObject.h"
#include "Component/AComponent.h"
#include <type_traits>

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	_components.clear();
}

void GameObject::SetActive(bool active)
{
	_isActive = active;
}

bool GameObject::IsActive()
{
	return _isActive;
}

void GameObject::SetTick(bool tick)
{
	_isTicking = tick;
}

bool GameObject::IsTicking()
{
	return _isTicking;
}

void GameObject::Tick(float deltaTime)
{
	if (!_isTicking) return;

	for (const auto& component : _components)
	{
		if(component.second != nullptr)
			component.second.get()->Update(deltaTime);
	}
}

template<class T>
void GameObject::AddComponent()
{
	static_assert(std::is_base_of<AComponent, T>::value, "T must inherit from type 'AComponent'");
	//_components.insert();
}

template<class T>
void GameObject::RemoveComponent()
{
	static_assert(std::is_base_of<AComponent, T>::value, "T must inherit from type 'AComponent'");
	const std::type_info& id = typeid(T);
	auto it = _components.find(id);
	if(it != _components.end())
		_components.erase(it);
}

template<class T>
std::weak_ptr<T> GameObject::GetComponent()
{
	static_assert(std::is_base_of<AComponent, T>::value, "T must inherit from type 'AComponent'");
	const std::type_info& id = typeid(T);
	auto it = _components.find(id);
	if (it != _components.end())
		_components.erase(it);
}