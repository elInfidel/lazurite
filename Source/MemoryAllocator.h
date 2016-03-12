#pragma once
#include <physx/PxPhysicsAPI.h>
#include <physx/PxScene.h>
#include <physx/pvd/PxVisualDebugger.h>

using namespace physx;

class MemoryAllocator : public PxAllocatorCallback
{
public:
	virtual ~MemoryAllocator();
	virtual void* allocate(size_t size, const char* typeName, const char* filename, int line);
	virtual void deallocate(void* ptr);
};

