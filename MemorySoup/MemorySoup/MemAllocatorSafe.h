#pragma once

#include "MemAllocator.h"

template<size_t MEM_SIZE>
class MemAllocatorSafe : public MemAllocator<MEM_SIZE>
{
public:
	void* end = nullptr;

	using Super = MemAllocator<MEM_SIZE>;

	MemAllocatorSafe()
	{
		createAllocator();
	}

	MemAllocatorSafe(MemAllocatorSafe&& rhs) noexcept
		: MemAllocator<MEM_SIZE>(std::move(rhs))
	{
		end = rhs.end;
		rhs.end = nullptr;
	}

	MemAllocatorSafe& operator=(MemAllocatorSafe&& rhs) noexcept
	{
		MemAllocator<MEM_SIZE>::operator=(std::move(rhs));
		end = rhs.end;
		rhs.end = nullptr;
		return *this;
	}

	void createAllocator()
	{
		Super::createAllocator();
		end = ((char*) this->data) + this->nbMaxElem * MEM_SIZE;
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

