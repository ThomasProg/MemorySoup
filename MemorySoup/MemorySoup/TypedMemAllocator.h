#pragma once

#include <iostream>
#include <memory>
#include <new>

template<typename T>
class TypedMemAllocator
{
public:
	union DataPointerUnion
	{
		T data;
		DataPointerUnion* next; // linked list
	};

	DataPointerUnion* data = nullptr;
	static constexpr size_t nbMaxElem = 50000000;

	DataPointerUnion* headPtr = nullptr;

	TypedMemAllocator()
	{
		data = static_cast<DataPointerUnion*> (malloc(sizeof(DataPointerUnion) * nbMaxElem));
		if (data == nullptr)
		{
			return;
		}

		for (size_t i = 0; i < nbMaxElem - 1; ++i)
		{
			data[i].next = &data[i+1];
		}
		data[nbMaxElem - 1].next = nullptr;

		headPtr = data;
	}

	template<typename ... ARGS>
	__forceinline T* addElem(ARGS&& ... args) noexcept
	{
		if (headPtr == nullptr)
		{
			return nullptr;
		}

		DataPointerUnion* newObjectMemLoc = headPtr;
		headPtr = headPtr->next;
		return &newObjectMemLoc->data;
	}

	__forceinline void removeElem(T* data) noexcept
	{
		DataPointerUnion* d = reinterpret_cast<DataPointerUnion*> (data);
		d->next = headPtr;
		headPtr = d;
	}
};

