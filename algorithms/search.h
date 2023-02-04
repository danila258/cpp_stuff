#ifndef SEARCH_H
#define SEARCH_H


template<typename Iter, typename T>
bool recursiveBinarySearch(Iter first, Iter last, T&& value)
{
    auto it = first + std::distance(first, last) / 2;

    if (first == last + 1)
    {
        return false;
    }

    if (*it < value)
    {
        return recursiveBinarySearch(it + 1, last, value);
    }
    else if (*it > value)
    {
        return recursiveBinarySearch(first, it - 1, value);
    }
    else
    {
        return true;
    }
}

template<typename Iter, typename T>
bool binarySearch(Iter first, Iter last, T&& value)
{
    int count = std::distance(first, last) / 2;

    while (count > 0)
    {
        count = std::distance(first, last) / 2;
        auto it = first + count;

        if (*it > value)
        {
            last = it - 1;
        }
        else if (*it < value)
        {
            first = it + 1;
        }
        else
        {
            return true;
        }
    }

    return false;
}


#endif //SEARCH_H
