#pragma once

#include "UnrolledListAllocator.hpp"

class Foo
{
    int a = 2;
    int b = 2;
    int c = 2;

public:
    inline static UnrolledListAllocator<Foo> allocator = UnrolledListAllocator<Foo>::fromNbElements(100); //UnrolledListAllocator<Foo>::fromBytes(1000);

public:
    // custom placement new
    static void* operator new(std::size_t size) 
    {
        return allocator.allocate(1); 
    }

    // custom placement delete
    static void operator delete(void* ptr)
    {
        allocator.deallocate(static_cast<Foo*>(ptr), 1);
    }
};