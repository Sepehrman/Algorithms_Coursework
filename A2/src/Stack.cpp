#include "../include/Stack.h"
using namespace std;

/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */


/**
 * The following constructor initializes the stack as a vector object and sets the currentsize to 0.
 */
template <typename T>
Stack<T>::Stack() {
    currentSize = 0;
    buffer = vector<T>();
}

/**
 * Checks if the current size of the stack is equal to zero (empty)
 * @return if the current Stack size is zero
 */
template <typename T>
bool Stack<T>::isEmpty() const {
    return currentSize == 0;
}

/**
 * Returns the size of the current Stack
 * @return the currentSize property of the Stack object
 */
template <typename T>
size_t Stack<T>::size() const {
    return currentSize;
}

/**
 * Adds an element to the Stack
 * @param element The generic type of an element we want to add to our stack. Increases the Stack size by 1
 */
template <typename T>
void Stack<T>::push(const T& element) {
    buffer.push_back(element);
    currentSize++;
}

/**
 * Removes an element from the top of the stack and decreases the size of the Stack by 1
 */
template <typename T>
void Stack<T>::pop() {
    buffer.pop_back();
    currentSize--;
}

/**
 * Returns the top-most element of the Stack
 * @return the .back() property of the current element
 */
template <typename T>
T& Stack<T>::top() {
    return  buffer.back();
}

/**
 * Returns the top-most element of the Stack
 * @return the .back() property of the current element
 */
template<typename T>
const T &Stack<T>::top() const {
    return buffer.back();
}