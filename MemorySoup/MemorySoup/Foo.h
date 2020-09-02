#pragma once
#include <iostream>
class Foo
{
public:
	int a = 1, b = 2, c = 3;

	Foo() = default;
	Foo(Foo&&) noexcept
	{

	}
	Foo(const Foo& f)
	{
	std::cout << "Copy" << std::endl;
	}
	Foo(int i)
	{

	}

	~Foo()
	{

	}

	__forceinline  static void* operator new(size_t size);
	__forceinline  static void operator delete(void* foo);
};