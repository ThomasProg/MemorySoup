#pragma once

#include <memory>

class MemAllocator
{
protected:
	void* data = nullptr;
public:
	static constexpr size_t nbMaxElem = 2 << 10;

	void* headPtr = nullptr;

	__inline MemAllocator(MemAllocator&& rhs) noexcept
	{
		data = rhs.data;
		headPtr = rhs.headPtr;
		rhs.data = nullptr;
		rhs.headPtr = nullptr;
	}

	__inline MemAllocator& operator=(MemAllocator&& rhs) noexcept
	{
		data = rhs.data;
		headPtr = rhs.headPtr;
		rhs.data = nullptr;
		rhs.headPtr = nullptr;
		return *this;
	}

	MemAllocator(size_t nbElements, size_t elementSize)
	{
		createAllocator(nbElements, elementSize);
	}

	void createAllocator(size_t nbElements, size_t elementSize)
	{
		data = malloc(elementSize * nbElements);
		if (data == nullptr)
		{
			return;
		}

		char* ptr = (char*)data;
		for (size_t i = 0; i < nbElements - 1; ++i)
		{
			void** p = (void**)(ptr + i * elementSize);
			*p = ptr + (i + 1) * elementSize;
		}
		void** p = (void**)(ptr + (nbElements - 1) * elementSize);
		*p = nullptr;

		headPtr = data;
		
	}

	__forceinline void* addElem() noexcept
	{
		if (headPtr == nullptr)
		{
			return nullptr;
		}

		void* newObjectMemLoc = headPtr;
		headPtr = *((void**)headPtr);
		return newObjectMemLoc;
	}

	__forceinline void removeElem(void* data) noexcept
	{
		//*((void**)(data)) = headPtr;
		//headPtr = data;
	}

	~MemAllocator()
	{
		if (data != nullptr)
		{
			free(data);
		}
	}
};