#ifndef STACK_LAB_LISTSTACK_H
#define STACK_LAB_LISTSTACK_H

#include "StackImplementation.h"

#include <list>

using ValueType = double;


class ListStack : public IStackImplementation {
public:
    ListStack() = default;

    void push(const ValueType& value) override;
    void pop() override;

    const ValueType& top() const override;
    bool isEmpty() const override;
    size_t size() const override;

private:
    std::list<ValueType> _listStack;

    void sizeCheck() const;
};


#endif //STACK_LAB_LISTSTACK_H
