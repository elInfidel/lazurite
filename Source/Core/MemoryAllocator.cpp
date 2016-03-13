#include "MemoryAllocator.h"

MemoryAllocator::~MemoryAllocator() {}

void* MemoryAllocator::allocate(size_t size, const char* typeName, const char* filename, int line)
{
	void* pointer = _aligned_malloc(size, 16);
	return pointer;
}

void MemoryAllocator::deallocate(void* ptr)
{
	_aligned_free(ptr);
}
