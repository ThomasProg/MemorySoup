#pragma once

#include <memory>

template<size_t MEM_SIZE>
class MemAllocator
{
protected:
	void* data = nullptr;
public:
	static constexpr size_t nbMaxElem = 2 << 10;

	void* headPtr = nullptr;

	static int b;
	int a = 0;

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

	MemAllocator()
	{
		b++;
		createAllocator();
	}

	void createAllocator()
	{
		data = malloc(MEM_SIZE * nbMaxElem);
		if (data == nullptr)
		{
			return;
		}

		char* ptr = (char*)data;
		for (size_t i = 0; i < nbMaxElem - 1; ++i)
		{
			void** p = (void**) (ptr + i * MEM_SIZE);
			*p = ptr + (i + 1) * MEM_SIZE;
		}
		void** p = (void**) (ptr + (nbMaxElem - 1) * MEM_SIZE);
		*p = nullptr;

		//for (size_t i = 0; i < nbMaxElem - 1; ++i)
		//{
		//	*((void**)(((char*)data) + i * MEM_SIZE)) = (((char*)data) + (i + 1) * MEM_SIZE);
		//}
		//*((void**)((char*)data + MEM_SIZE * (nbMaxElem - 1))) = nullptr;

		headPtr = data;
		
	}

	__forceinline void* addElem() noexcept
	{
		if (headPtr == nullptr)
		{
			return nullptr;
		}
		a++;
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

template<size_t MEM_SIZE>
int MemAllocator<MEM_SIZE>::b = 0;