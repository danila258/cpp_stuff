#ifndef CLRS_TASKS_H
#define CLRS_TASKS_H


std::vector<int> bitPlus(std::vector<int>& one, std::vector<int>& two)
{
    if (two.size() > one.size())
    {
        std::swap(one, two);
    }

    std::vector<int> arr(one.size() + 1);

    bool remnant = false;
    auto first = one.rbegin();
    auto result = arr.rbegin();

    for (auto second = two.rbegin(); second != two.rend(); ++second)
    {
        *result = (*second + *first + remnant) % 2;
        remnant = (*second + *first + remnant > 1);

        ++result;
        ++first;
    }

    while( first != one.rend() )
    {
        *result = (*first + remnant) % 2;
        remnant = (*first + remnant > 1);

        ++result;
        ++first;
    }

    if (one.size() == two.size())
    {
        *arr.begin() = remnant;
    }

    return arr;
}


template<typename T>
void mergeInversions(T& arr, typename T::iterator start, typename T::iterator mid, typename T::iterator end, int& count)
{
    T arr1(start, mid);
    T arr2(mid, end);

    auto i = arr1.begin();
    auto j = arr2.begin();

    if (arr1.size() == 1 && arr2.size() == 1)
    {
        count += arr1[0] > arr2[0];
    }

    while (i != arr1.end() && j != arr2.end())
    {
        if (*i <= *j)
        {
            count += std::distance(arr2.begin(), j);
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
        count += arr2.size() * std::distance(i, arr1.end());
        std::move(i, arr1.end(), start);
    }
}

template<typename T>
void calculateInversions(T& arr, typename T::iterator start, typename T::iterator end, int& count)
{
    if (start != end - 1)
    {
        auto mid = start + std::distance(start, end) / 2;

        calculateInversions(arr, mid, end, count);
        calculateInversions(arr, start, mid, count);
        mergeInversions(arr, start, mid, end, count);
    }
}

template<typename T>
int inversions(T& arr)
{
    if (arr.empty())
    {
        return 0;
    }

    int count = 0;
    calculateInversions(arr, arr.begin(), arr.end(), count);

    return count;
}


#endif //CLRS_TASKS_H
