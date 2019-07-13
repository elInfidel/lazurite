#include "GameObject.h"
#include "Component/AComponent.h"
#include <type_traits>

GameObject::GameObject()
{
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	componentList.clear();
}

void GameObject::SetActive(bool active)
{
	_isActive = active;
}

bool GameObject::IsActive() const
{
	return _isActive;
}

void GameObject::Tick(float deltaTime)
{
	for (const auto& component : componentList)
	{
		if(component.second != nullptr && component.second.get()->IsActive())
			component.second.get()->Tick(deltaTime);
	}
}