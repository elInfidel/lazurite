#include "component/AComponent.h"
#include "GameObject.h"

AComponent::AComponent() { }
AComponent::~AComponent() { }

bool AComponent::IsActive()
{
	return _isActive;
}

std::shared_ptr<GameObject> AComponent::GetOwningObject()
{
	return gameObject;
}
