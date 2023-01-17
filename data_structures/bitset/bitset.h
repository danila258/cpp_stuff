#ifndef BITSET_H
#define BITSET_H

#include <string>
#include <cmath>


constexpr size_t compileTimeCeil(float num)
{
    const size_t n = static_cast<size_t>(num);
    return (num > n)? n + 1 : n;
}


template<size_t N, typename T = char>
class bitset
{
private:
    char _data[ compileTimeCeil(float(N) / (sizeof(T) * 8)) ] = {};

    struct bit_reference
    {
        T* chunk;
        size_t pos;

        bit_reference& operator=(bool value);
        operator bool() const;
    };

public:
    bitset<N>() = default;
    bitset(const bitset<N,T>& other);
    bitset(bitset<N,T>&& other) noexcept;

    bitset<N,T>& operator=(const bitset<N,T>& other);
    bitset<N,T>& operator=(bitset<N,T>&& other);

    void set(size_t pos);
    void set();

    void reset(size_t pos);
    void reset();

    void flip(size_t pos);
    void flip();

    std::string to_string() const;

    bitset<N,T>::bit_reference operator[](size_t pos);
};


template<size_t N, typename T>
typename bitset<N,T>::bit_reference& bitset<N,T>::bit_reference::operator=(bool value)
{
    if (value)
    {
        *chunk |= (T(1) << pos);
    }
    else
    {
        *chunk &= ~(T(1) << pos);
    }

    return *this;
}

template<size_t N, typename T>
bitset<N,T>::bit_reference::operator bool() const
{
    return *chunk & (T(1) << pos);
}

template<size_t N, typename T>
bitset<N,T>::bitset(const bitset<N,T>& other)
{
    for (size_t i = 0; i < N; ++i)
    {
        _data[i] = other._data[i];
    }
}

template<size_t N, typename T>
bitset<N,T>::bitset(bitset<N,T>&& other) noexcept
{
    *this = std::move(other);
}

template<size_t N, typename T>
bitset<N,T>& bitset<N,T>::operator=(const bitset<N,T>& other)
{
    if (this == &other)
    {
        return *this;
    }

    bitset<N,T> copy(other);
    *this = std::move(copy);

    return *this;
}

template<size_t N, typename T>
bitset<N,T>& bitset<N,T>::operator=(bitset<N,T>&& other)
{
    if (this == &other)
    {
        return *this;
    }

    std::swap(_data, other._data);

    return *this;
}

template<size_t N, typename T>
void bitset<N,T>::set(size_t pos)
{
    size_t chunkIndex = pos / (sizeof(T) * 8);

    if (chunkIndex > 0)
    {
        pos -= chunkIndex * sizeof(T) * 8;
    }

    *(_data + chunkIndex) |= (T(1) << pos);
}

template<size_t N, typename T>
void bitset<N,T>::set()
{
    for (size_t i = 0; i < N; ++i)
    {
        set(i);
    }
}

template<size_t N, typename T>
void bitset<N,T>::reset(size_t pos)
{
    size_t chunkIndex = pos / (sizeof(T) * 8);

    if (chunkIndex > 0)
    {
        pos -= chunkIndex * sizeof(T) * 8;
    }

    *(_data + chunkIndex) &= ~(1 << pos);
}

template<size_t N, typename T>
void bitset<N,T>::reset()
{
    for (size_t i = 0; i < N; ++i)
    {
        reset(i);
    }
}

template<size_t N, typename T>
void bitset<N,T>::flip(size_t pos)
{
    size_t chunkIndex = pos / (sizeof(T) * 8);

    if (chunkIndex > 0)
    {
        pos -= chunkIndex * sizeof(T) * 8;
    }

    *(_data + chunkIndex) ^= (1 << pos);
}

template<size_t N, typename T>
void bitset<N,T>::flip()
{
    for (size_t i = 0; i < N; ++i)
    {
        flip(i);
    }
}

template<size_t N, typename T>
std::string bitset<N,T>::to_string() const
{
    std::string line;
    line.reserve(N);

    for (int i = 0; i < compileTimeCeil(float(N) / (sizeof(T) * 8)); ++i)
    {
        for (int j = 0; j < sizeof(T) * 8; ++j)
        {
            if (i * (sizeof(T) * 8) + j == N)
            {
                break;
            }

            if ((*(_data + i) & (T(1) << j)) == 0)
            {
                line += '0';
            }
            else
            {
                line += '1';
            }
        }
    }

    return line;
}

template<size_t N, typename T>
typename bitset<N,T>::bit_reference bitset<N,T>::operator[](size_t pos)
{
    size_t chunkIndex = pos / (sizeof(T) * 8);

    if (chunkIndex > 0)
    {
        pos -= chunkIndex * sizeof(T) * 8;
    }

    return {_data + chunkIndex, pos};
}


#endif //BOOL_ARRAY_H
