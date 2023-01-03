#ifndef STACK_LAB_STACK_H
#define STACK_LAB_STACK_H

#include <iostream>

using ValueType = double;

enum class StackContainer {
    Vector = 0,
    List,
};

class IStackImplementation;


class Stack {
public:
    Stack(StackContainer container = StackContainer::Vector);
    Stack(const ValueType* valueArray, size_t arraySize,
          StackContainer container = StackContainer::Vector);

    explicit Stack(const Stack& copyStack);
    Stack& operator=(const Stack& copyStack);

    Stack(Stack&& moveStack) noexcept;
    Stack& operator=(Stack&& moveStack) noexcept;

    ~Stack();

    void push(const ValueType& value);
    void pop();

    const ValueType& top() const;
    bool isEmpty() const;
    size_t size() const;

private:
    IStackImplementation* _pimpl = nullptr;
    StackContainer _containerType;
};


#endif //STACK_LAB_STACK_H
