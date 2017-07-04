#include "GameObject.h"
#include "Component/AComponent.h"
#include <type_traits>

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < _components.size(); ++i)
		delete _components[i];

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

void GameObject::Update(float deltaTime)
{
	for (vector<AComponent*>::iterator component = _components.begin(); component != _components.end(); ++component)
		(*component)->Update(deltaTime);
}

template<class T>
void GameObject::AddComponent()
{
	//TODO: Implement duplicate check
	components.push_back(newComponent);
}

template<class T>
void GameObject::RemoveComponent()
{
	static_assert(std::is_base_of<AComponent, T>::value, " Template type must inherit from AComponent. ");

	for (auto it = _components.begin(); it != _components.end(); ++it)
	{
		T* c = dynamic_cast<T*>((*it));

		if (c != nullptr)
		{
			_components.erase(it);
			delete c;
			return;
		}
	}
}

template<class T>
T* GameObject::GetComponent()
{
	static_assert(std::is_base_of<AComponent, T>::value, " Template type must inherit from AComponent. ");

	//TODO: I'd like to improve this by mapping component pointers using their type as a key.
	for (vector<AComponent*>::iterator component = _components.begin(); component != _components.end(); ++component)
	{
		T* c = dynamic_cast<T*>((*component));

		if (c != nullptr)
		{
			return c;
		}
	}
}