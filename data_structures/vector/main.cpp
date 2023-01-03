#include <iostream>
#include "Vector.h"

void print(Vector& array) {
    for (auto&& item : array) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

int main() {
    double array[5] = {1, 2, 3, 4, 5};
    Vector arr(array, 5);

    std::cout << arr[0] << "\n";

    arr.pushBack(6);
    arr.pushFront(0);
    print(arr);

    arr.erase(0, 1);
    arr.eraseBetween(0, 1);
    print(arr);

    arr.popBack();
    arr.popFront();
    print(arr);

    arr.insert(-1, 0);
    print(arr);

    std::cout << arr.find(-1) << "\n";

    arr.reserve(20);
    std::cout << arr.capacity() << "\n";

    arr.shrinkToFit();
    std::cout << arr.capacity() << " == " << arr.size() << "\n";
    std::cout << arr.loadFactor() << "\n";

    return 0;
}
