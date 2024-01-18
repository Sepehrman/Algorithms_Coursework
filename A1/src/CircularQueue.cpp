#include "../include/CircularQueue.h"
using namespace std;


template<typename T>
CircularQueue<T>::CircularQueue(int capacity) {
    buffer = vector<T>(capacity);
    currentSize = buffer.size();
    rearIndex = 0;
    frontIndex = buffer.size();

}

template<typename T>
bool CircularQueue<T>::isFull() const {
    return buffer.size() == capacity;
}

template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return buffer.size() == 0;
}

template<typename T>
size_t CircularQueue<T>::size() const {
    return currentSize;
}

template<typename T>
void CircularQueue<T>::enqueue(const T &element) {
//    currentSize++;
//    buffer.push_back(element);
//    if (!isFull()) {
//        buffer.push_back(element);
//    }
}

template<typename T>
void CircularQueue<T>::dequeue() {
//    buffer.erase(buffer.begin() + currentSize-1);
//    currentSize--;
}

template<typename T>
T &CircularQueue<T>::front() {
    return buffer.front();
}


template<typename T>
const T &CircularQueue<T>::front() const {
    return buffer.front();
}

