#include "../include/CircularQueue.h"
using namespace std;


/**
 * The following constructor initializes the values for our Circular Queue. Where by default our size starts from 0
 * and the rearIndex & frontIndex are set to 0 in the initial state. Our vector is then resized to a specific capacity
 * which is the size in which our vector can withhold.
 * When it comes to enqueue & dequeue, we would need to come up with a way for our data structure to start from the
 * 0th position once we reach the end for our vector. We use the formula (Index + 1) % Capacity to reset the position
 * of our rear & front indices
 * @param capacity The capacity in which we are resizing our vector to be
 */
template<typename T>
CircularQueue<T>::CircularQueue(int capacity) {
    currentSize = 0;
    rearIndex = 0;
    frontIndex = 0;
    buffer.resize(capacity);
}

/**
 * Checks if the size of the Queue equals the capacity
 * @return A boolean on whether the currentSize of the Queue is equal to the given capacity
 */
template<typename T>
bool CircularQueue<T>::isFull() const {
    return currentSize == capacity;
}

/**
 * Checks if the size of the current CircularQueue is empty
 * @return if the currentSize of the queue is 0
 */
template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return currentSize == 0;
}

/**
 * Returns the size of the current CircularQueue
 * @return the currentSize of the Queue
 */
template<typename T>
size_t CircularQueue<T>::size() const {
    return currentSize;
}

/**
 * Sets the new element to the current rearIndex
 * Then moves up the rearIndex by one every time enqueue is called and checks whether we have reached the end of the Queue
 * or not, using the formula (rearIndex + 1) % capacity. And finally we increment the size of the Queue by one.
 */
template<typename T>
void CircularQueue<T>::enqueue(const T &element) {

    if (!isFull()) {
        buffer[rearIndex] = element;
        rearIndex = (rearIndex + 1) % capacity;
        ++currentSize;
    }
}

/**
 * Moves up the frontIndex by one every time dequeue is called and checks whether we have reached the end of the Queue
 * or not, using the formula (frontIndex + 1) % capacity. And finally we decrement the size of the Queue by one.
 */
template<typename T>
void CircularQueue<T>::dequeue() {
    if (!isEmpty()) { ;
        frontIndex = (frontIndex + 1) % capacity;
        --currentSize;
    }
}

/**
 * Provides the element of our element which our frontIndex is located at
 * @return the frontIndex element of the vector
 */
template<typename T>
T &CircularQueue<T>::front() {
    return buffer[frontIndex];
}

/**
 * Provides the element of our element which our frontIndex is located at
 * @return the frontIndex element of the vector
 */
template<typename T>
const T &CircularQueue<T>::front() const {
    return buffer[frontIndex];
}
