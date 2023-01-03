#ifndef BST_LAB_MAP_H
#define BST_LAB_MAP_H

#include "BST.h"

#include <stdexcept>


template <typename Key, typename Value>
class Map
{
    BinarySearchTree<Key, Value> _tree;
public:
    using MapIterator = typename BinarySearchTree<Key, Value>::Iterator;
    using ConstMapIterator = typename BinarySearchTree<Key, Value>::ConstIterator;

    Map() = default;

    explicit Map(const Map& other);
    Map& operator=(const Map& other);

    explicit Map(Map&& other) noexcept;
    Map& operator=(Map&& other) noexcept;

    ~Map() = default;

    // вставить элемент с ключем key и значением value
    // если узел с ключем key уже представлен, то заменить его значение на value
    void insert(const Key& key, const Value& value);

    // удалить элемент с ключем key
    void erase(const Key& key);

    // найти элемент, равный ключу key
    ConstMapIterator find(const Key& key) const;
    MapIterator find(const Key& key);

    // доступ к элементу по ключу
    // если в момент обращения элемента не существует, создать его,
    // ключ равен key, value равно дефолтному значению для типа Value
    const Value& operator[](const Key& key) const;
    Value& operator[](const Key& key);

    MapIterator begin();
    MapIterator end();

    ConstMapIterator cbegin() const;
    ConstMapIterator cend() const;

    size_t size() const;
};


template<typename Key, typename Value>
Map<Key, Value>::Map(const Map& other)
{
    *this = other;
}

template<typename Key, typename Value>
Map<Key, Value>& Map<Key, Value>::operator=(const Map& other)
{
    _tree = other._tree;
}

template<typename Key, typename Value>
Map<Key, Value>::Map(Map&& other) noexcept
{
    *this = std::move(other);
}

template<typename Key, typename Value>
Map<Key, Value> &Map<Key, Value>::operator=(Map&& other) noexcept
{
    _tree = std::move(other._tree);
}

template<typename Key, typename Value>
void Map<Key, Value>::insert(const Key& key, const Value& value)
{
    if (_tree.find(key) != _tree.end())
    {
        _tree.erase(key);
    }

    _tree.insert(key, value);
}

template<typename Key, typename Value>
void Map<Key, Value>::erase(const Key& key)
{
    _tree.erase(key);
}

template<typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::find(const Key& key) const
{
    return ConstMapIterator( _tree.find(key) );
}

template<typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::find(const Key& key)
{
    return MapIterator ( _tree.find(key) );
}

template<typename Key, typename Value>
const Value& Map<Key, Value>::operator[](const Key& key) const
{
    int mSize = _tree.size();

    if (find(key) == end())
    {
        insert(key, Value());
    }

    if (mSize != _tree.size())
    {
        throw std::out_of_range("");
    }

    return _tree.find(key)->second;
}

template<typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key& key)
{
    if (_tree.find(key) == _tree.end())
    {
        insert(key, Value());
    }

    return _tree.find(key)->second;
}

template<typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::begin()
{
    return MapIterator( _tree.begin() );
}

template<typename Key, typename Value>
typename Map<Key, Value>::MapIterator Map<Key, Value>::end()
{
    return MapIterator( _tree.end() );
}

template<typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::cbegin() const
{
    return ConstMapIterator( _tree.cbegin() );
}

template<typename Key, typename Value>
typename Map<Key, Value>::ConstMapIterator Map<Key, Value>::cend() const
{
    return ConstMapIterator( _tree.cend() );
}

template<typename Key, typename Value>
std::size_t Map<Key, Value>::size() const
{
    return _tree.size();
}


#endif //BST_LAB_MAP_H
