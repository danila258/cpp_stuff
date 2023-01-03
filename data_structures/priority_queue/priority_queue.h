#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <iostream>


template<typename T, typename Container = std::vector<T>>
class priority_queue
{
public:
    void push(const T& obj);
    void pop();

    const T& top();
    bool empty();
    void print();

private:
    Container _container;

    void siftUp(int index);
    void siftDown(int index);
};


template<typename T, typename Container>
void priority_queue<T, Container>::push(const T& obj)
{
    _container.push_back(obj);
    this->siftUp(_container.size() - 1);
}

template<typename T, typename Container>
void priority_queue<T, Container>::pop()
{
    if ( empty() )
    {
        throw std::runtime_error("");
    }

    std::swap(_container[0], _container[_container.size() - 1]);
    _container.pop_back();
    siftDown(0);
}

template<typename T, typename Container>
const T &priority_queue<T, Container>::top()
{
    return _container.at(0);
}

template<typename T, typename Container>
bool priority_queue<T, Container>::empty()
{
    return !_container.size();
}

template<typename T, typename Container>
void priority_queue<T, Container>::print()
{
    for (auto&& item : _container)
    {
        std::cout << item << ' ';
    }

    std::cout << '\n';
}

template<typename T, typename Container>
void priority_queue<T, Container>::siftUp(int index)
{
    if (!index)
    {
        return;
    }

    int parent = (index + index % 2) / 2 - 1;

    if (_container[parent] < _container[index])
    {
        std::swap(_container[index], _container[parent]);
        siftUp(parent);
    }
}

template<typename T, typename Container>
void priority_queue<T, Container>::siftDown(int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int cur;

    if ( left >= _container.size() ) {
        return;
    }
    else if ( right >= _container.size() ) {
        cur = left;
    }
    else
    {
        cur = (_container[left] > _container[right]) ? left : right;
    }

    if (_container[index] < _container[cur])
    {
        std::swap(_container[cur], _container[index]);
        siftDown(cur);
    }
}


#endif //PRIORITY_QUEUE_H
