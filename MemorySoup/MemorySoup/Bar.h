#pragma once

class Bar
{
public:
	int a = 1, b = 2, c = 3;

	Bar() = default;

	Bar(int i)
	{

	}

	~Bar() = default;

	__forceinline  static void* operator new(size_t size);
	__forceinline  static void operator delete(void* foo);
};