#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H


class StackAllocator
{
public:
    StackAllocator() = delete;

    explicit StackAllocator(size_t size) : _freeSize(size)
    {
        _data = new char[size];
        _pointer = _data;
    }

    ~StackAllocator()
    {
        delete[] _data;
    }

    template<typename T>
    T* allocate()
    {
        if (sizeof(T) + sizeof(std::size_t) > _freeSize)
        {
            throw std::bad_alloc();
        }

        T* result = reinterpret_cast<T*>(_pointer);
        _pointer = (char*)_pointer + sizeof(T);
        new (_pointer) size_t(sizeof(T));
        _pointer = (char*)_pointer + sizeof(size_t);

        _freeSize -= sizeof(T) + sizeof(std::size_t);

        return result;
    }

    void deallocate()
    {
        if (_pointer == _data)
        {
            return;
        }

        _pointer = (char*)_pointer - sizeof(std::size_t);
        std::size_t size = *reinterpret_cast<std::size_t*>(_pointer);
        _pointer = (char*)_pointer - size;
    }

    template<typename T, typename... Args>
    void construct(T* xp, Args&&... args)
    {
        new (xp) T(std::forward<Args>(args)...);
    }

    template<typename T>
    void destroy(T* xp)
    {
        xp->~T();
    }

private:
    char* _data;
    void* _pointer;
    std::size_t _freeSize;
};


#endif //STACKALLOCATOR_H
