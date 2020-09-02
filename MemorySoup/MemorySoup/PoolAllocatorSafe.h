#pragma once

#include "PoolAllocator.h"

class MemAllocatorSafe : public MemAllocator
{
public:
	void* end = nullptr;

	using Super = MemAllocator;

	MemAllocatorSafe(size_t nbElements, size_t elementSize)
	{
		createAllocator(nbElements, elementSize);
	}

	MemAllocatorSafe(MemAllocatorSafe&& rhs) noexcept
		: MemAllocator(std::move(rhs))
	{
		end = rhs.end;
		rhs.end = nullptr;
	}

	MemAllocatorSafe& operator=(MemAllocatorSafe&& rhs) noexcept
	{
		MemAllocator::operator=(std::move(rhs));
		end = rhs.end;
		rhs.end = nullptr;
		return *this;
	}

	void createAllocator(size_t nbElements, size_t elementSize)
	{
		Super::createAllocator(nbElements, elementSize);
		end = ((char*) this->data) + nbElements * elementSize;
	}

	__forceinline void* addElem() noexcept
	{
		return Super::addElem();
	}

	__forceinline bool removeElem(void* data) noexcept
	{
		if (data == nullptr)
			return true;
		if (this->data <= data && this->end >= data)
		{
			Super::removeElem(data);
			return true;
		}
		else 
		{
			return false;
		}
	}
};

