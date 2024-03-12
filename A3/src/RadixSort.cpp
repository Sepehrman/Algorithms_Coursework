/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/RadixSort.h"

/**
 * Sort using Radix Sort
 */
template <typename T>
void RadixSort<T>::sort() {
    int time = getMaxDigitCount(); // the max digit count among elements
    int digit = 1;
    while (time > 0) { // Iterates over each digit place from the least significant to the most
        countingSort(digit);
        digit++;
        time--;
    }
}

/**
 * Get the Max Digit Count among all the elements
 * @return an Integer, indicating the max digit count
 */
template <typename T>
int RadixSort<T>::getMaxDigitCount() {
    int biggestKey = 0; // Holds the biggest key among elements

    for (const T& element : elements_) { // Iterates over all elements
        int key = getKeyFunction_(element);
        if (biggestKey < key){ // If the current key is larger than the biggestKey, set biggest Key to current
            biggestKey = key;
        }
    }
    return getDigitCount(biggestKey);
}

/**
 * Get the number's digit count given a number
 */
template <typename T>
int RadixSort<T>::getDigitCount(int number) {
    if (number == 0) {
        return 1;
    }
    int count = 0;
    int theNumber = number;
    while (theNumber != 0){
        theNumber = theNumber / 10;
        count++;
    }
    return count;
}

/**
 * Sort based on the digit value one time.
 */
template <typename T>
void RadixSort<T>::countingSort(int digit) {
    std::vector<T> output(elements_.size());
    int count[10] = {0};

    for (const T& element : elements_) {
        int key = getKeyFunction_(element);
        int keyDigit = getDigitValue(key, digit);
        count[keyDigit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = elements_.size() - 1; i >= 0; i--) {
        int key = getKeyFunction_(elements_[i]);
        int keyDigit = getDigitValue(key, digit);
        output[count[keyDigit] - 1] = elements_[i];
        count[keyDigit]--;
    }

    for (int i = 0; i < elements_.size(); i++) {
        elements_[i] = output[i];
    }
}

/**
 * Get the digit number at the digit place.
 */
template <typename T>
int RadixSort<T>::getDigitValue(int number, int digit) {
    int theDigitNumber = 0;
    while (digit > 1){
        number = number / 10;
        digit--;
    }
    theDigitNumber = number % 10;
    return theDigitNumber;
}