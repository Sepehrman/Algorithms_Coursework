#include "../include/CircularQueue.h"
using namespace std;


/**
 * The following constructor initiallizes the values for our Circular Queue. Where by default our size starts from 0
 * and the rearIndex & frontIndex are set to 0 it is defined in the form of a placement in which our next element is
 * placed. The rearIndex would remain
 * @tparam T Generic Function Type
 * @param capacity The capacity in which we are resizing our vector to be
 */
template<typename T>
CircularQueue<T>::CircularQueue(int capacity) {
    currentSize = 0;
    rearIndex = 0;
    frontIndex = 0;
    buffer.resize(capacity);
}

template<typename T>
bool CircularQueue<T>::isFull() const {
    return currentSize == capacity;
}

template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return currentSize == 0;
}

template<typename T>
size_t CircularQueue<T>::size() const {
    return currentSize;
}

template<typename T>
void CircularQueue<T>::enqueue(const T &element) {

    if (!isFull()) {
        buffer[rearIndex] = element;
        rearIndex = (rearIndex + 1) % capacity;
        ++currentSize;
    }
}

template<typename T>
void CircularQueue<T>::dequeue() {
    if (!isEmpty()) { ;
        frontIndex = (frontIndex + 1) % capacity;
        --currentSize;
    }
}

template<typename T>
T &CircularQueue<T>::front() {
    return buffer[frontIndex];
}


template<typename T>
const T &CircularQueue<T>::front() const {
    return buffer[frontIndex];
}

