#pragma once

#include <memory>
#include <cassert>

class StackAllocator
{
protected:
	void* data = nullptr;
	void* last = nullptr;

public:
	StackAllocator() = default;

	StackAllocator(size_t size)
	{
		reserve(size);
	}

	StackAllocator(const StackAllocator&) = delete;
	StackAllocator& operator=(const StackAllocator&) = delete;
	StackAllocator(StackAllocator&& rhs) noexcept
		: data(rhs.data), last(rhs.last)
	{
		data = rhs.data;
		last = rhs.last;
		rhs.data = nullptr;
		rhs.last = nullptr;
	}
	StackAllocator& operator=(StackAllocator&& rhs) noexcept
	{
		if (data != nullptr)
		{
			free(data);
		}
		data = rhs.data;
		last = rhs.last;
		rhs.data = nullptr;
		rhs.last = nullptr;
		return *this;
	}

	void reserve(size_t size)
	{
		assert(data == nullptr);
		last = data = malloc(size);
	}

	template<typename T>
	T* push()
	{
		T* newObject = (T*) last;
		last = ((char*)last) + sizeof(T);
		return newObject;
	}

	void pop(void* d, size_t size)
	{
		last = ((char*)last) - size;
	}
	
	template<typename T>
	__inline void pop(T* d)
	{
		pop(d, sizeof(T));
	}

	void clearFront()
	{
		last = data;
	}

	~StackAllocator()
	{
		if (data != nullptr)
		{
			free(data);
		}
	}
};

using FrameAllocator = StackAllocator;
