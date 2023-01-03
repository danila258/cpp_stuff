#include <iostream>
#include <stdexcept>

using Value = double;

class Iterator {
        public:
        explicit Iterator(Value* ptr) : _ptr(ptr) {}

        Value & operator*() {
            return *_ptr;
        }

        const Value& operator*() const {
            return *_ptr;
        }

        Value* operator->() {
            return _ptr;
        }

        const Value* operator->() const {
            return _ptr;
        }

        Iterator operator++() {
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {
            Value* bufPtr = _ptr;
            ++_ptr;
            return Iterator(bufPtr);
        }

        Iterator operator--() {
            --_ptr;
            return *this;
        }

        Iterator operator--(int) {
            Value* bufPtr = _ptr;
            --_ptr;
            return Iterator(bufPtr);
        }

        bool operator==(const Iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        private:
        Value* _ptr;
};


class Vector
{
public:
    Vector() = default;
    Vector(const Value* rawArray, const size_t size, float coef = 2.0f);

    ~Vector();

    explicit Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    explicit Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    Value& operator[](size_t idx);
    const Value& operator[](size_t idx) const;

    void pushBack(const Value& value);
    void pushFront(const Value& value);

    void insert(const Value& value, size_t pos);
    void insert(const Value* values, size_t size, size_t pos);
    void insert(const Vector& vector, size_t pos);

    void popBack();
    void popFront();

    void erase(size_t pos, size_t count = 1);
    void eraseBetween(size_t beginPos, size_t endPos);

    size_t size() const;
    size_t capacity() const;
    double loadFactor() const;

    long long find(const Value& value) const;

    void reserve(size_t capacity);
    void shrinkToFit();

    Iterator begin() {
        return Iterator(&(_data[0]));
    }

    Iterator end() {
        return Iterator(&_data[_size]);
    }

private:
    Value* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    float _multiplicativeCoef = 2.0f;

    void sizeControl(size_t size);
    void errorShow() const;
};


