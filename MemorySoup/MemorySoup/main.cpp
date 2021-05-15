#include "UnrolledListAllocator.hpp"
#include "Bar.h"
#include "Foo.h"
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& out, const UnrolledListAllocator<T>& list)
{
    for (typename UnrolledListAllocator<T>::Node* currentNode = list.firstNode; currentNode != list.lastNode->next; currentNode = currentNode->next)
    {
        std::cout << "===============\n";
        std::cout << "size : " <<  list.m_size << '\n';
        for (typename UnrolledListAllocator<T>::SubNode* p = currentNode->getSubNodes(); p < currentNode->getSubNodes() + list.m_size; p++)
        {
            std::cout << "Current Node : " << p << "\t/\t";
            std::cout << p->next - p << "   /   " << p->next << std::endl;
        }
        std::cout << "===============\n";
    }

    return out;
}

void oneNodeTest()
{
    Foo* f = new Foo();
    Foo* f2 = new Foo();

    std::cout << (Foo::allocator) << std::endl;    

    delete f;
    delete f2;

    std::cout << (Foo::allocator) << std::endl;   
}

// Test the integrity of UnrolledListAllocator if multiple nodes are added
void multipleNodesTest()
{
    Foo* f[5];
    for (int i = 0; i < 5; i++)
    {
        f[i] = new Foo();
    }

    std::cout << (Foo::allocator) << std::endl;    

    for (int i = 0; i < 5; i++)
    {
        delete f[i];
    }

    // Foo* ff = new Foo();

    std::cout << "\n\n\n\n\n" << std::endl;
    std::cout << (Foo::allocator) << std::endl;   
}

#include <chrono>
#include <bits/stdc++.h>
#include <new>

template<template<typename> class ALLOCATOR>
void perfTest()
{
	ALLOCATOR<Bar> allocator;

    auto start = std::chrono::high_resolution_clock::now();
  
    constexpr size_t size = 100000;
    Bar* f[size];
    for (size_t i = 0; i < size; i++)
    {
		f[i] = allocator.allocate(1);
        new (f[i]) Bar();
    }

    for (size_t i = 0; i < size; i++)
    {
		f[i]->~Bar();
		allocator.deallocate(f[i], 1);
    }
  
    auto end = std::chrono::high_resolution_clock::now();
  
    // Calculating total time taken by the program.
    double time_taken = 
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  
    time_taken *= 1e-9;
  
    std::cout << "Time taken is : " << std::fixed 
         << time_taken << std::setprecision(9);
    std::cout << " sec" << std::endl;
}

int main()
{
    // multipleNodesTest();

	std::cout << "default allocator : \n"; 
    perfTest<std::allocator>();

	std::cout << "UnrolledListAllocator : \n"; 
	perfTest<UnrolledListAllocator>();

    // {
    //     std::unique_ptr<Bar> f = std::make_unique<Bar>();
    //     std::cout << (Bar::allocator) << std::endl;   
    // }

    // std::cout << (Bar::allocator) << std::endl;   
}