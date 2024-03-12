/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/MergeSort.h"
using namespace std;

/**
 * Merge sort method. Recursive and Split into smallest size
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

    sort(left);
    sort(right);
    merge(arr, left, right);

}

//Merge merge method.
template <typename T>
void MergeSort<T>::merge(std::vector<T>& arr, const std::vector<T>& left, const std::vector<T>& right){
    int leftPointer = 0;
    int rightPointer = 0;
    int arrayPointer = 0;

    while(leftPointer < left.size() && rightPointer < right.size()){
        if(compare(left[leftPointer], right[rightPointer])){
            arr[arrayPointer] = left[leftPointer];
            leftPointer++;
            arrayPointer++;
        } else {
            arr[arrayPointer] = right[rightPointer];
            rightPointer++;
            arrayPointer++;
        }
    }
        while (leftPointer < left.size()) {
            arr[arrayPointer++] = left[leftPointer++];
        }
        while (rightPointer < right.size()) {
            arr[arrayPointer++] = right[rightPointer++];
        }
}

template class MergeSort<int>;