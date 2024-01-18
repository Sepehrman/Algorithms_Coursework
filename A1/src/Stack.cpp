//
// Created by Sepehr on 2024-01-18.
//
// Implement the functions inside the Stack.h

#include "../include/Stack.h"
using namespace std;

template <typename T>
Stack<T>::Stack() {
    currentSize = 0;
    buffer = vector<T>();
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return currentSize == 0;
}

template <typename T>
size_t Stack<T>::size() const {
   return currentSize;
}

template <typename T>
void Stack<T>::push(const T& element) {
    buffer.push_back(element);
    currentSize++;
}

template <typename T>
void Stack<T>::pop() {
    buffer.pop_back();
    currentSize--;
}

template <typename T>
T& Stack<T>::top() {
    return  buffer.back();
}

template<typename T>
const T &Stack<T>::top() const {
    return buffer.back();
}


