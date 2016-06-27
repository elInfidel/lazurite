#pragma once

class MemoryAllocator
{
public:
	virtual ~MemoryAllocator();

protected:
	void* AllocAligned();
	void FreeAligned(void* ptr);
};

