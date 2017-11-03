#pragma once

class MemoryAllocator
{
public:
	virtual ~MemoryAllocator();

protected:
	void* allocAligned();
	void freeAligned(void* ptr);
};

