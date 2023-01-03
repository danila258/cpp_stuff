#include "VectorStack.h"

#include <stdexcept>

void VectorStack::push(const ValueType &value) {
    _vectorStack.pushBack(value);
}

void VectorStack::pop() {
    sizeCheck();
    _vectorStack.popBack();
}

const ValueType &VectorStack::top() const {
    sizeCheck();
    return _vectorStack[size() - 1];
}

bool VectorStack::isEmpty() const {
    return _vectorStack.size() == 0;
}

size_t VectorStack::size() const {
    return _vectorStack.size();
}

void VectorStack::sizeCheck() const {
    if (size() != 0) {
        return;
    }

    throw std::out_of_range("empty vector");
}