#ifndef SET_H
#define SET_H

#include "Map.h"


template <typename Value>
class Set
{
    Map<Value, Value> _map;

public:
    using SetIterator = typename Map<Value, Value>::MapIterator;
    using ConstSetIterator = typename Map<Value, Value>::ConstMapIterator;

    Set() = default;

    explicit Set(const Set& other);
    Set& operator=(const Set& other);

    explicit Set(Set&& other) noexcept;
    Set& operator=(Set&& other) noexcept;

    ~Set() = default;

    void insert(const Value& value);

    void erase(const Value& value);

    ConstSetIterator find(const Value& value) const;
    SetIterator find(const Value& key);

    bool contains(const Value& value) const;
};


template<typename Value>
Set<Value>::Set(const Set& other)
{
    *this = other;
}

template<typename Value>
Set<Value>& Set<Value>::operator=(const Set& other)
{
    _map = other._map;
}

template<typename Value>
Set<Value>::Set(Set&& other) noexcept
{
    *this = std::move(other);
}

template<typename Value>
Set<Value>& Set<Value>::operator=(Set&& other) noexcept
{
    _map = std::move(other._map);
}

template<typename Value>
void Set<Value>::insert(const Value& value)
{
    _map.insert(value, value);
}

template<typename Value>
void Set<Value>::erase(const Value& value)
{
    _map.erase(value);
}

template<typename Value>
typename Set<Value>::ConstSetIterator Set<Value>::find(const Value& value) const
{
    return _map.find(value);
}

template<typename Value>
typename Set<Value>::SetIterator Set<Value>::find(const Value& key)
{
    return _map.find(key);
}

template<typename Value>
bool Set<Value>::contains(const Value& value) const
{
    return find(value) != _map.cend();
}


#endif //SET_H
