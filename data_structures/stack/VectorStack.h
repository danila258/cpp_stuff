#ifndef STACK_LAB_VECTORSTACK_H
#define STACK_LAB_VECTORSTACK_H

#include "StackImplementation.h"
#include "Vector.h"

using ValueType = double;


class VectorStack : public IStackImplementation {
public:
    VectorStack() = default;

    void push(const ValueType& value) override;
    void pop() override;

    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;

private:
    Vector _vectorStack;

    void sizeCheck() const;
};


#endif //STACK_LAB_VECTORSTACK_H
