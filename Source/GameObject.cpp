#include "GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

Transform GameObject::GetTransform()
{
	return transform;
}

void GameObject::AddComponent(AComponent* newComponent)
{
	//TODO: Implement duplicate check
	components.push_back(newComponent);
}

void GameObject::Update(float deltaTime)
{
	for (vector<AComponent*>::iterator component = components.begin(); component != components.end(); ++component)
	{
		(*component)->update(deltaTime);
	}
}

template<class T>
void GameObject::RemoveComponent(T remove)
{
	if (dynamic_cast<AComponent>(T) == nullptr)
		return;

	for (vector<AComponent*>::iterator component = components.begin(); component != components.end(); ++component)
	{
		T* c = dynamic_cast<T*>((*component));

		if (c != nullptr)
		{
			components.erase(component);
			delete c;
			return;
		}
	}
}

template<class T>
T* GameObject::GetComponent(T get)
{
	if (dynamic_cast<AComponent>(T) == nullptr)
		return;

	for (vector<AComponent*>::iterator component = components.begin(); component != components.end(); ++component)
	{
		T* c = dynamic_cast<T*>((*component));

		if (c != nullptr)
		{
			return c;
		}
	}
}