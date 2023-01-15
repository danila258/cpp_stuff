#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

template<typename T>
class StackAllocator
{
public:
    StackAllocator() = delete;

    StackAllocator(size_t size) : _freeSize(size), _pointer(_data)
    {
        _data = new(size);
    }

    ~StackAllocator()
    {
        delete data;
    }

    T* allocate(size_t n)
    {
        if (n + sizeof(std::size_t) > _freeSize)
        {
            throw std::bad_alloc();
        }

        T* result = reinterpret_cast<T*>(_pointer);
        _pointer = (char*)_pointer + n;
        ::operator new (_pointer) std::size_t(n)
        _pointer = (char*)_pointer + sizeof(std::size_t);

        _freeSize -= n + sizeof(std::size_t);
        _count += 1;

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

    template<typename... Args>
    void construct(T* xp, Args&&... args)
    {
        new (xp) T(std::forward<Args>(args)...);
    }

    void destroy(T* xp)
    {
        xp->~T();
    }

private:
    void* _data;
    void* _pointer;
    std::size_t _freeSize;
};


#endif //STACKALLOCATOR_H
