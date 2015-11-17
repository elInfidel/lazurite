#include "GameObject.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::AddComponent(AComponent* newComponent)
{
	//TODO: Implement duplicate check
	components.push_back(newComponent);
}

void GameObject::Update()
{
	for (AComponent* component : components)
	{
		component->update();
	}
}
