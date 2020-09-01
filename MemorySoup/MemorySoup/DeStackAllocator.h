#pragma once

#include "StackAllocator.h"

class DeStackAllocator : public StackAllocator
{
protected:
	void* backLast = nullptr;

public:
	using Super = StackAllocator;

	void reserve(size_t size)
	{
		Super::reserve(size);
		backLast = ((char*)(data)) + size;
	}

	template<typename T>
	T* push_back()
	{
		((char*)backLast) -= sizeof(T);
		return backLast;
	}

	void pop_back(void* d, size_t size)
	{
		backLast = ((char*)last) + size;
	}

	template<typename T>
	__inline void pop_back(T* d)
	{
		pop_back(d, sizeof(T));
	}
};

