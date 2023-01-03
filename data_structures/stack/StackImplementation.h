#ifndef STACK_LAB_STACKIMPLEMENTATION_H
#define STACK_LAB_STACKIMPLEMENTATION_H

#include <iostream>

using ValueType = double;


class IStackImplementation {
public:
    virtual void push(const ValueType& value) = 0;
    virtual void pop() = 0;

    virtual const ValueType& top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t size() const = 0;

    virtual ~IStackImplementation() = default;
};


#endif //STACK_LAB_STACKIMPLEMENTATION_H