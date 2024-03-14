/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/MergeSort.h"
using namespace std;

/**
 * Merge sort method. Recursively Split into smallest size
 * @param arr an array (Vector) of elements
 */
template <typename T>
void MergeSort<T>::sort(std::vector<T>& arr){

    if (arr.size() <= 1) {
        return;
    }

    // Find the size of the mid-point of the array
    int mid = arr.size() / 2 ;

    // separate mergesort into two left-half & right-half lists
    vector<T> left = vector<T>(arr.begin(), arr.begin() + mid);
    vector<T> right = vector<T>(arr.begin() + mid, arr.end());

    sort(left); // Recursively sort the left array
    sort(right); // Recursively sort the right array
    merge(arr, left, right); // Pointer for the merged array

}

/**
 * Our Merge Method that does the sorting from our recursive sort method
 * @param arr a Pointer to our original array
 * @param left a Pointer to our left array
 * @param right a Pointer to our right array
 */
template <typename T>
void MergeSort<T>::merge(std::vector<T>& arr, const std::vector<T>& left, const std::vector<T>& right){

    int arrayPointer = 0;
    int leftPtr = 0;
    int rightPtr = 0;

    // Merge the left and right arrays into the main array in sorted order while they are at the given size.
    while(leftPtr < left.size() && rightPtr < right.size()){
        // Compare if the element of the left or right array are bigger
        // sets the element to the arrayPointer and increases the arrayPointer & the left/right pointer index by 1
        if(compare(left[leftPtr], right[rightPtr])){
            arr[arrayPointer] = left[leftPtr];
            leftPtr++;
            arrayPointer++;
        } else {
            arr[arrayPointer] = right[rightPtr];
            rightPtr++;
            arrayPointer++;
        }
    }

    // Copy any remaining elements from the left or right array.
        while (leftPtr < left.size()) {
            arr[arrayPointer++] = left[leftPtr++];
        }
        while (rightPtr < right.size()) {
            arr[arrayPointer++] = right[rightPtr++];
        }
}

