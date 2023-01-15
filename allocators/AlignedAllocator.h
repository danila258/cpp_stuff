#ifndef ALIGNEDALLOCATOR_H
#define ALIGNEDALLOCATOR_H


template <std::size_t N>
class AlignedAllocator
{
public:
    AlignedAllocator() : _pointer(_data), _freeSize(N)
    {}

    template<typename T>
    T* alignedAlloc( size_t alignment = alignof(T) )
    {
        if (std::align(alignment, sizeof(T), _pointer, _freeSize))
        {
            T* result = reinterpret_cast<T*>(_pointer);
            _pointer = (char*)_pointer + sizeof(T);
            _freeSize -= sizeof(T);

            return result;
        }

        throw std::bad_alloc();
    }

private:
    char _data[N];
    void* _pointer;
    std::size_t _freeSize;
};


#endif //ALIGNEDALLOCATOR_H
