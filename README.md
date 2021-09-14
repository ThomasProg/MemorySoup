# MemorySoup

MemorySoup contains optimized allocators and containers.

## UnrolledListAllocator
- Fast allocations and fast deallocations.
- Approximatively 10x faster than std::allocator on some benchmarks.
- Elements are close to each other in memory, so it is cache friendly.
- Can't allocate arrays. 

## SortedVector
A vector that is sorted automatically.

## UnrolledListContainer
A container that guarantees : 
- The adress of the contained elements will keep the same adress; a pointer to a valid element will not be invalided except when the element is destroyed.
- O(log(n)) insertion complexity
- O(log(n)) erasure complexity
- VERY FAST iteration in for each loops. Indeed, elements are close in memory and the iteration will happen in a cache friendly order.
