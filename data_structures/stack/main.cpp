#include "Stack.h"

#include <iostream>

int main() {
    Stack a;

    std::cout << a.isEmpty() << "\n";
    std::cout << a.size() << "\n";

    a.push(5);
    std::cout << a.isEmpty() << "\n";
    std::cout << a.size() << "\n";

    std::cout << a.top() << "\n";

    a.pop();
    std::cout << a.isEmpty() << "\n";
    std::cout << a.size() << "\n";

    a.push(5);
    Stack b;
    b = a;
    std::cout << b.isEmpty() << "\n";
    std::cout << b.size() << "\n";

    return 0;
}
