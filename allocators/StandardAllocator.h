#ifndef STANDARDALLOCATOR_H
#define STANDARDALLOCATOR_H

#include <stdlib.h>


template<typename T>
struct StandardAllocator
{
    typedef T value_type;

    StandardAllocator() = default;

    template<class U>
    constexpr StandardAllocator(const StandardAllocator <U>&) noexcept {}

    T* allocate(size_t n)
    {
        return reinterpret_cast<T*>( ::operator new(n * sizeof(T)) );
    }

    void deallocate(T* p, size_t n)
    {
        ::operator delete(p);
    }

    template<typename... Args>
    void construct(T* xp, Args&&... args)
    {
        new (xp) T(std::forward<Args>(args)...);
    }

   void destroy(T* xp)
   {
        xp->~T();
   }
};

template<class T, class U>
bool operator==(const StandardAllocator<T>&, const StandardAllocator<U>&) { return true; }

template<class T, class U>
bool operator!=(const StandardAllocator<T>&, const StandardAllocator<U>&) { return false; }


#endif //STANDARDALLOCATOR_H
