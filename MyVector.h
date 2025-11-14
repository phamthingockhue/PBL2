#pragma once

#include <stdexcept>
#include <iostream>

template<typename T>
class MyVector {
private:
    T* data;
    size_t _size;
    size_t _capacity;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i)
            new_data[i] = data[i];

        delete[] data;
        data = new_data;
        _capacity = new_capacity;
    }

public:
    MyVector() : data(nullptr), _size(0), _capacity(0) {}

    MyVector(size_t initialCapacity) : _capacity(initialCapacity), _size(0) {
        data = new T[_capacity];
    }

    MyVector(const MyVector& other) : _capacity(other._capacity), _size(other._size) {
        data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i)
            data[i] = other.data[i];
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            _capacity = other._capacity;
            _size = other._size;
            data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~MyVector() {
        delete[] data;
    }

    T& operator[](size_t index) {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    T& at(size_t index) {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= _size)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    T& front() {
        if (_size == 0) throw std::out_of_range("Vector is empty");
        return data[0];
    }

    T& back() {
        if (_size == 0) throw std::out_of_range("Vector is empty");
        return data[_size - 1];
    }

    T* getData() { return data; }
    const T* getData() const { return data; }

    bool empty() const { return _size == 0; }
    size_t get_size() const { return _size; }
    size_t get_capacity() const { return _capacity; }

    void reserve(size_t new_capacity) {
        if (new_capacity > _capacity)
            resize(new_capacity);
    }

    void shrink_to_fit() {
        if (_size < _capacity)
            resize(_size);
    }

    void push_back(const T& value) {
        if (_size == _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            resize(new_capacity);
        }
        data[_size++] = value;
    }

    void pop_back() {
        if (_size > 0)
            --_size;
    }

    void clear() { _size = 0; }

    void erase(size_t index) {
        if (index >= _size)
            throw std::out_of_range("Index out of range");

        for (size_t i = index; i < _size - 1; ++i)
            data[i] = data[i + 1];
        --_size;
    }

    void insert(size_t index, const T& value) {
        if (index > _size)
            throw std::out_of_range("Index out of range");

        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            resize(new_capacity);
        }

        for (size_t i = _size; i > index; --i)
            data[i] = data[i - 1];

        data[index] = value;
        ++_size;
    }

    T* begin() { return data; }
    const T* begin() const { return data; }
    T* end() { return data + _size; }
    const T* end() const { return data + _size; }

    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < _size; ++i) {
            std::cout << data[i];
            if (i < _size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};