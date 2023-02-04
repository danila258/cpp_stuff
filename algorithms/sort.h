#ifndef SORT_H
#define SORT_H


template<typename T>
void insertionSort(T& arr)
{
    for (auto i = arr.begin() + 1; i != arr.end(); ++i)
    {
        auto j = i - 1;

        while(*j > *(j + 1))
        {
            std::iter_swap(j, j + 1);
            --j;

            if (j == arr.begin())
            {
                break;
            }
        }
    }
}


template<typename T>
void recursiveIntersectionSort(T& arr, typename T::iterator start)
{
    auto j = start - 1;

    while(*j > *(j + 1))
    {
        std::iter_swap(j, j + 1);

        if (j == arr.begin())
        {
            break;
        }

        --j;
    }

    if (start == arr.end() - 1)
    {
        return;
    }

    recursiveIntersectionSort(arr, ++start);
}


template<typename T>
void selectionSort (T& arr)
{
    typename T::iterator min;

    for (auto i = arr.begin(); i != arr.end() - 1; ++i)
    {
        min = i;

        for (auto j = i; j != arr.end(); ++j)
        {
            if (*j < *min)
            {
                min = j;
            }
        }

        std::iter_swap(min, i);
    }
}


template<typename T>
void recursiveMerge(typename T::iterator start, typename T::iterator mid, typename T::iterator end)
{
    T arr1(start, mid);
    T arr2(mid, end);

    auto i = arr1.begin();
    auto j = arr2.begin();

    while (i != arr1.end() && j != arr2.end())
    {
        if (*i <= *j)
        {
            *start = std::move(*i);
            ++i;
        }
        else
        {
            *start = std::move(*j);
            ++j;
        }

        ++start;
    }

    if (i == arr1.end())
    {
        std::move(j, arr2.end(), start);
    }
    else
    {
        std::move(i, arr1.end(), start);
    }
}

template<typename T>
void recursiveMergeSort(typename T::iterator start, typename T::iterator end)
{
    if (start != end - 1)
    {
        auto mid = start + std::distance(start, end) / 2;

        sort(mid, end);
        sort(start, mid);
        recursiveMerge(start, mid, end);
    }
}


template<typename T>
std::vector<T> merge(std::vector<T>& a, std::vector<T>& b)
{
    std::vector<T> c;
    c.reserve(a.size() + b.size());

    auto i = a.begin();
    auto j = b.begin();

    while (i != a.end() && j != b.end())
    {
        if (*i <= *j)
        {
            c.push_back(*i);
            ++i;
        }
        else
        {
            c.push_back(*j);
            ++j;
        }
    }

    if (i == a.end())
    {
        std::move(j, b.end(), std::back_inserter(c));
    }
    else
    {
        std::move(i, a.end(), std::back_inserter(c));
    }

    return c;
}

template<template<typename, typename> class U, typename T, typename A>
void mergeSort(U<T,A>& arr)
{
    std::queue<std::vector<T>> q;
    std::for_each(arr.begin(), arr.end(), [&q](T& n){ q.push({n}); });

    while (q.size() > 1)
    {
        std::vector<T> a = q.front();
        q.pop();
        std::vector<T> b = q.front();
        q.pop();

        q.push(merge(a, b));
    }

    std::move(q.front().begin(), q.front().end(), arr.begin());
}


template<typename T>
void bubbleSort(T& arr)
{
    if (arr.size() < 2)
    {
        return;
    }

    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        for (auto j = arr.end() - 1; j != i; --j)
        {
            if (*j < *(j - 1))
            {
                std::iter_swap(j, j - 1);
            }
        }
    }
}


#endif //SORT_H