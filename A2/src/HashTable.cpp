#include "HashTable.h"
#include <functional> // for std::hash


/**
 * Hash function to generate a hashkey given a key
 * @param key a Generic object type of key
 * @return an Integer Hash Key
 */
template<typename KeyType>
size_t hashKey(const KeyType& key) {
    return std::hash<KeyType>{}(key);
}


/**
 * A constructor responsible for initializing a hashtable
 * @param size an integer that initializes the size of our hashtable
 * @param threshold a double representing our loadfactor
 */
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(unsigned int size, double threshold) {
    tableSize = size;
    hashTable = std::vector<Bucket>(tableSize);
    loadFactorThreshold = threshold;
}

/**
 * An interator responsible for returning an element at the beginning of our hashtable
 * @return a hashtable interable that returns the beginning of our hashtable
 */
template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::begin() {
    return Iterator(hashTable.begin(), hashTable.end());
}

/**
 * An interator responsible for returning an element at the end of our hashtable
 * @return a hashtable interable that returns the end of our hashtable
 */
template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::end() {
    return Iterator(hashTable.end(), hashTable.end());
}

template<typename KeyType, typename ValueType>
ValueType& HashTable<KeyType, ValueType>::operator[](const KeyType& key) {
    unsigned int index = hashKey(key) % tableSize;
    while (hashTable[index].occupied && hashTable[index].key != key) {
        index = (index + 1) % tableSize;
    }
    if (!hashTable[index].occupied) {
        hashTable[index].key = key;
        hashTable[index].occupied = true;
    }
    return hashTable[index].value;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::updateValueForKey(const KeyType& key, ValueType newValue) {
    unsigned int index = hashKey(key) % tableSize;
    while (hashTable[index].occupied && hashTable[index].key != key) {
        index = (index + 1) % tableSize;
    }
    if (hashTable[index].occupied) {
        hashTable[index].value = newValue;
    }
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    if (loadFactor() > loadFactorThreshold) {
        rehash();
    }

    unsigned int index = hashKey(key) % tableSize;
    unsigned int currentHop = 0;
    unsigned int freeSlotIndex = findFreeSlot(hashTable, index, currentHop);

    if (freeSlotIndex != tableSize) {
        hashTable[freeSlotIndex].key = key;
        hashTable[freeSlotIndex].value = value;
        hashTable[freeSlotIndex].occupied = true;
        hashTable[index].hopInfo |= (1 << currentHop);
    }
}

template<typename KeyType, typename ValueType>
ValueType* HashTable<KeyType, ValueType>::search(const KeyType& key) {
    unsigned int index = hashKey(key) % tableSize;
    while (hashTable[index].occupied) {
        if (hashTable[index].key == key) {
            return &(hashTable[index].value);
        }
        index = (index + 1) % tableSize;
    }
    return nullptr;
}

template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType& key) {
    unsigned int index = hashKey(key) % tableSize;
    while (hashTable[index].occupied) {
        if (hashTable[index].key == key) {
            hashTable[index].occupied = false;
            // Reorganize hop information
            for (unsigned int i = 0; i < hopRange; ++i) {
                if (hashTable[index].hopInfo & (1 << i)) {
                    hashTable[index].hopInfo &= ~(1 << i);
                    break;
                }
            }
            return true;
        }
        index = (index + 1) % tableSize;
    }
    return false;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clear() {
    for (auto& bucket : hashTable) {
        bucket.occupied = false;
        bucket.hopInfo = 0;
    }
}

template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::size() const {
    unsigned int count = 0;
    for (const auto& bucket : hashTable) {
        if (bucket.occupied) {
            ++count;
        }
    }
    return count;
}

template<typename KeyType, typename ValueType>
double HashTable<KeyType, ValueType>::loadFactor() const {
    return static_cast<double>(size()) / static_cast<double>(tableSize);
}

template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::findFreeSlot(std::vector<Bucket>& cTable, unsigned int startIndex, unsigned int& currentHop) {
    for (unsigned int i = 0; i < hopRange; ++i) {
        if (!(cTable[startIndex].hopInfo & (1 << i))) {
            currentHop = i;
            return startIndex + i;
        }
    }

    return tableSize;
}

template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash() {
    // Temporary storage for old table
    std::vector<Bucket> oldTable = hashTable;

    tableSize *= 2;
    hashTable.resize(tableSize);
    clear();

    // Re-insert elements into the new table
    for (const auto& bucket : oldTable) {
        if (bucket.occupied) {
            insert(bucket.key, bucket.value);
        }
    }
}
