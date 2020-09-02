#include <iostream>

#include "TypedPoolAllocator.h"

#include "PoolAllocator.h"

#include "PoolAllocatorSafe.h"

#include "Foo.h"
#include "Bar.h"

#include "DoubleBufferedFrameAllocated.h"

#include <vector>

template<size_t SIZE>
class Alloc
{
public:
	static std::vector<MemAllocatorSafe> memAllocator;
	
	__forceinline static void* allocate()
	{
		void* data;
		for (MemAllocatorSafe& allocator : memAllocator)
		{
			data = allocator.addElem();
			if (data != nullptr)
			{
				return data;
			}
		}

		memAllocator.emplace_back(50, SIZE);
		return memAllocator.back().addElem();
	}

	__forceinline static void deallocate(void* data)
	{
		for (MemAllocatorSafe& allocator : memAllocator)
		{
			if (allocator.removeElem(data))
			{
				return;
			}
		}
	}
};

template<size_t SIZE>
std::vector<MemAllocatorSafe> Alloc<SIZE>::memAllocator;



__forceinline void* Foo::operator new(size_t size)
{
	return Alloc<sizeof(Foo)>::allocate();
}

__forceinline void Foo::operator delete(void* foo)
{
	Alloc<sizeof(Foo)>::deallocate(foo);
}

__forceinline void* Bar::operator new(size_t size)
{
	return Alloc<sizeof(Bar)>::allocate();
}

__forceinline void Bar::operator delete(void* foo)
{
	Alloc<sizeof(Bar)>::deallocate(foo);
}


#include <chrono>
#include <ctime>

void benchmark()
{
	static constexpr int n = 500;

	//for (int i = 0; i < 10; i++)
	//Alloc<sizeof(Foo)>::memAllocator.emplace_back();

	int i;
	std::cin >> i;
	auto start = std::chrono::system_clock::now();

	Foo* foos[n];
	Bar* bars[n];

	for (int i = 0; i < n; i++)
	{
		foos[i] = new Foo(i);
	}

	for (int i = 0; i < n; i++)
	{
		delete foos[i];
	}

	for (int i = 0; i < n; i++)
	{
		bars[i] = new Bar(i);
	}

	for (int i = 0; i < n; i++)
	{
		delete bars[i];
	}

	//for (int i = n; i > 0; i--)
	//{
	//	delete foos[i - 1];
	//}

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "time : " << elapsed_seconds.count() << std::endl;
	std::cin >> i;
	start = std::chrono::system_clock::now();
	//for (int i = 0; i < n; i++)
	//{
	//	::delete ::new Foo(i);
	//	::delete ::new Bar(i);
	//}
	for (int i = 0; i < n; i++)
	{
		foos[i] = ::new Foo(i);
	}

	for (int i = 0; i < n; i++)
	{
		::delete foos[i];
	}

	for (int i = 0; i < n; i++)
	{
		bars[i] = ::new Bar(i);
	}

	for (int i = 0; i < n; i++)
	{
		::delete bars[i];
	}

	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "time : " << elapsed_seconds.count() << std::endl;

	std::cin >> i;
	start = std::chrono::system_clock::now();
	for (int i = 0; i < n; i++)
	{
		Foo f(i);
	}
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "time : " << elapsed_seconds.count() << std::endl;

	//TypedMemAllocator<Foo>::DataPointerUnion* ptr = memAllocator.headPtr;
	//int counter = 0;
	//while (ptr->next != nullptr)
	//{
	//	ptr = ptr->next;
	//	counter++;
	//}
	//std::cout << counter << std::endl;
}

class Koo
{
	int* foo = nullptr;

public:
	void updateWrite(DoubleBufferedFrameAllocated& buffer)
	{
		if (foo == nullptr)
		{
			foo = buffer.write<int>();
			*foo = 0;
		}
		else
		{
			int f = *foo;
			foo = buffer.write<int>();
			(*foo) = f + 1;
		}
		//foo->a ++;
	}

	void updateRead(const DoubleBufferedFrameAllocated& buffer)
	{
		if (foo != nullptr)
		{
			// Use foo
			std::cout << *foo << std::endl;
		}
	}
};

void readKoo(Koo& koo, DoubleBufferedFrameAllocated& buffer)
{
	koo.updateRead(buffer);
}

void writeKoo(Koo& koo, DoubleBufferedFrameAllocated& buffer)
{
	koo.updateWrite(buffer);
}

#include <thread>
#include <memory>
int main()
{
	//Alloc<sizeof(Foo)>::memAllocator.reserve(1000);

	benchmark();

	//std::cout << Alloc<sizeof(Bar)>::memAllocator.size() << std::endl;
	//static constexpr int n = 500;
	//Foo* foos[n];

	//for (int i = 0; i < n; i++)
	//{
	//	foos[i] = new Foo(i);
	//}

	//for (int i = 0; i < n; i++)
	//{
	//	delete foos[i];
	//}


	//std::unique_ptr<Foo> foo (new Foo());

	//Foo* r = foo.release();

	//std::shared_ptr<Foo> f(new Foo());


	//delete r;



	//DoubleBufferedFrameAllocated buffer;
	//Koo koo;

	//for (int i = 0; i < 10; i++)
	//{
	//	std::thread write(writeKoo, std::ref(koo), std::ref(buffer));
	//	std::thread read(readKoo, std::ref(koo), std::ref(buffer));

	//	write.join();
	//	read.join();

	//	buffer.swapBuffers();
	//}
}