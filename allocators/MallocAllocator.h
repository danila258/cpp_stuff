#ifndef MALLOCALLOCATOR_H
#define MALLOCALLOCATOR_H

#include <cstdlib>
#include <stdlib.h>
#include <new>
#include <limits>


template<typename T>
struct MallocAllocator
{
    typedef T value_type;

    MallocAllocator() = default;

    template<class U>
    constexpr MallocAllocator(const MallocAllocator <U>&) noexcept {}

    T* allocate(size_t n)
    {
        if (n * sizeof(T) > std::numeric_limits<std::size_t>::max())
            throw std::bad_array_new_length();

        if ( auto p = static_cast<T*>(std::malloc(n * sizeof(T))) )
            return p;

        throw std::bad_alloc();
    }

    void deallocate(T* p, size_t n)
    {
        std::free(p);
    }
};

template<class T, class U>
bool operator==(const MallocAllocator<T>&, const MallocAllocator<U>&) { return true; }

template<class T, class U>
bool operator!=(const MallocAllocator<T>&, const MallocAllocator<U>&) { return false; }


#endif //MALLOCALLOCATOR_H
