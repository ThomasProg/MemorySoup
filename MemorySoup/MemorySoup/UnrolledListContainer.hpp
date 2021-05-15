#pragma once

#include "SortedVector.hpp"
#include "UnrolledListAllocator.hpp"

template<typename T>
class UnrolledListContainer : protected SortedVector<T*>
{
private:
    using Super = SortedVector<T*>;

    UnrolledListAllocator<T> allocator;

public:
    using iterator = typename Super::iterator;

    template<typename ... ARGS>
    iterator emplace(ARGS&& ... args)
    {
        T* newElement = allocator.allocate(1);
        new (newElement) T(args...);
        return Super::insert(newElement);
    }

    void erase(T* value)
    {
        allocator.deallocate(value, 1);
        Super::erase(value);
    }

    inline void clear()
    {
        Super::clear();
    }

    iterator begin()
    {
        return Super::begin();
    }

    iterator end()
    {
        return Super::end();
    }
};