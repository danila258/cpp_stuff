#include <iostream>
#include "priority_queue.h"


int main() {
    priority_queue<int> pri;

    std::cout << "is empty = " << pri.empty() << '\n';

    pri.push(5);
    pri.push(1);
    pri.push(6);
    pri.push(3);
    pri.push(4);
    pri.push(7);
    pri.push(2);


    pri.print();
    std::cout << "top = " << pri.top() << '\n';

    while ( !pri.empty() ) {
        std::cout << pri.top() << std::endl;
        pri.pop();
    }

    return 0;
}
