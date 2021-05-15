#pragma once

#include <vector>

template<typename T, typename ALLOCATOR = std::allocator<T>>
class SortedVector
{
private:
    std::vector<T, ALLOCATOR> vec;

public:
    using iterator = typename std::vector<T, ALLOCATOR>::iterator;

    iterator insert(const T& inserted)
    {
        return vec.insert(std::upper_bound(vec.begin(), vec.end(), inserted), inserted);
    }

    void erase(const T& value)
    {
        auto pair = std::equal_range(vec.begin(), vec.end(), value);
        vec.erase(pair.first, pair.second);
    }

    inline void clear()
    {
        vec.clear();
    }

    iterator begin()
    {
        return vec.begin();
    }

    iterator end()
    {
        return vec.end();
    }
};