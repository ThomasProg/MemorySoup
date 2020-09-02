#pragma once

template <class T>
struct MyAllocator
{
	typedef T value_type;

	MyAllocator() = default;
	template <class U> constexpr MyAllocator(const MyAllocator <U>&) noexcept {}

	[[nodiscard]] T* allocate(size_t n) {
		if (n > std::numeric_limits<size_t>::max() / sizeof(T))
			throw std::bad_alloc();

		if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
			report(p, n);
			return p;
		}

		throw std::bad_alloc();
	}

	void deallocate(T* p, size_t n) noexcept {
		report(p, n, 0);
		std::free(p);
	}

private:
	void report(T* p, size_t n, bool alloc = true) const {
		std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
			<< " bytes at " << std::hex << std::showbase
			<< reinterpret_cast<void*>(p) << std::dec << '\n';
	}
};

template <class T, class U>
bool operator==(const MyAllocator <T>&, const MyAllocator <U>&) { return true; }
template <class T, class U>
bool operator!=(const MyAllocator <T>&, const MyAllocator <U>&) { return false; }