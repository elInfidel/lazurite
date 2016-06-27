#include "Physics.h"
#include "MemoryAllocator.h"
#include "../ImguiImpl.h"

Physics::Physics()
{
	if (isInitialized)
		Shutdown();
}


Physics::~Physics()
{
	if (isInitialized)
		Shutdown();
}

void Physics::Initialize()
{

}

void Physics::Update(float deltaTime)
{
	if (deltaTime <= 0) return;

}

void Physics::Shutdown()
{

}
