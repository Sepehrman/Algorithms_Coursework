/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */


#include "../include/HashTable.h"

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int size, double threshold) {
    hashTable = std::vector<Bucket>();
    hashTable.resize(size);
    tableSize = 0;
    loadFactorThreshold = threshold;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType &key, const ValueType &value) {
    unsigned int index = hashKey(key) % tableSize;
    hashTable[index] = value;


    tableSize++;
//    hashTable.insert(bucket.key, bucket);
}


template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::updateValueForKey(const KeyType &key, ValueType newValue) {

}

template<typename KeyType, typename ValueType>
ValueType *HashTable<KeyType, ValueType>::search(const KeyType &key) {
    return nullptr;
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType &key) {
    return false;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clear() {

}

template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::size() const {
    return tableSize;
}

template<typename KeyType, typename ValueType>
double HashTable<KeyType, ValueType>::loadFactor() const {
    return 0;
}

template<typename KeyType, typename ValueType>
unsigned int
HashTable<KeyType, ValueType>::findFreeSlot(vector<Bucket> &cTable, unsigned int startIndex, unsigned int &currentHop) {
    return 0;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash() {

}

template <typename KeyType, typename ValueType>
ValueType& HashTable<KeyType, ValueType>::operator[](const KeyType& key) {
    return hashTable[0].value;
}

template <typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::begin() {
    return Iterator(hashTable.begin(), hashTable.end());
}

// Iterator end function
template <typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::end() {
    return Iterator(hashTable.end(), hashTable.end());
}

