#include "ListStack.h"

void ListStack::push(const ValueType& value) {
    _listStack.push_back(value);
}

void ListStack::pop() {
    sizeCheck();
    _listStack.pop_back();
}

const ValueType& ListStack::top() const {
    sizeCheck();
    return _listStack.back();
}

bool ListStack::isEmpty() const {
    return _listStack.empty();
}

size_t ListStack::size() const {
    return _listStack.size();
}

void ListStack::sizeCheck() const {
    if (size() != 0) {
        return;
    }

    throw std::out_of_range("empty list");
}