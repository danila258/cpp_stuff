#ifndef ALIGNEDALLOCATOR_H
#define ALIGNEDALLOCATOR_H


template <std::size_t N>
class AlignedAllocator
{
public:
    AlignedAllocator() : pointer(data), freeSize(N)
    {}

    template<typename T>
    T* alignedAlloc( size_t alignment = alignof(T) )
    {
        if (std::align(alignment, sizeof(T), pointer, freeSize))
        {
            T* result = reinterpret_cast<T*>(pointer);
            pointer = (char*)pointer + sizeof(T);
            freeSize -= sizeof(T);

            return result;
        }

        throw std::bad_alloc();
    }

private:
    char data[N];
    void* pointer;
    std::size_t freeSize;
};


#endif //ALIGNEDALLOCATOR_H
