#include "CoreSystem.h"

bool CoreSystem::isInitialized = false;

CoreSystem::CoreSystem()
{
}


CoreSystem::~CoreSystem()
{
}

bool CoreSystem::IsInitialized()
{
	return isInitialized;
}
