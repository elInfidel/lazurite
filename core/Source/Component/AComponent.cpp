#include "AComponent.h"
#include "GameObject.h"

AComponent::AComponent()
{

}

AComponent::~AComponent()
{
}

bool AComponent::IsActive()
{
	return _isActive;
}
