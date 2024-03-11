/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/MergeSort.h"

//Merge sort method. Recursive and Split into smallest size,
template <typename T>
void MergeSort<T>::sort(std::vector<T>& arr){

    if (arr.size() <= 1) {
        return;
    }
    int mid = arr.size() / 2 ;

    std::vector<T> left (arr.begin(), arr.begin() + mid);
    std::vector<T> right (arr.begin() + mid, arr.end());

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