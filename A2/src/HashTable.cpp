/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "HashTable.h"

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
    typename std::vector<Bucket>::iterator it = hashTable.begin();
    while (it != hashTable.end() && !it->occupied) {
        ++it;
    }
    return Iterator(it, hashTable.end());
}


/**
 * An interator responsible for returning an element at the end of our hashtable
 * @return a hashtable interable that returns the end of our hashtable
 */
template<typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::end() {
    return Iterator(hashTable.end(), hashTable.end());
}

/**
 * Overloaded function call for the operator to get or modify the value of a given key.
 * @param key the key that's associated value is retrieved or modified
 * @return A reference to the value with the given key
 */
template<typename KeyType, typename ValueType>
ValueType& HashTable<KeyType, ValueType>::operator[](const KeyType& key) {
    unsigned int index = hashKey(key) % tableSize;

    // Linear probing to handle possible collisions
    while (hashTable[index].occupied && hashTable[index].key != key) {
        index = (index + 1) % tableSize;
    }
    // If the key is not occupied, insert into the hashtable
    if (!hashTable[index].occupied) {
        hashTable[index].key = key;
        hashTable[index].occupied = true;
    }
    return hashTable[index].value;
}

/**
 * Insert an element in our hashtable given the key & value
 * @param key the key of the element we are inserting our value into in the hashtable
 * @param value the value of the element we are inserting in the hashtable
 */
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    // Checks if the given loadfactor threshold is less than the existing load factor of our hashtable.
    // If true, then rehash & doubles the size of our hashtable
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

/**
 * Looks for a given key within the hashtable, then returns it
 * @param key a Key we are searching for in the hashtable
 * @return a Value indicating whether the element exists in our hashtable. If it doesn;t exist, returns nullptr
 */
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

/**
 * Removes a key/element from our hashtable. undoing the occupancy, then resetting
 * all neighbouring elements within our hop range.
 * @param key a Key Type representing the key we want to remove
 * @return A Boolean indicating whether we were able to remove the element or not
 */
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType& key) {
    unsigned int index = hashKey(key) % tableSize;
    while (hashTable[index].occupied) {
        if (hashTable[index].key == key) {
            hashTable[index].occupied = false;
            // Reorganize hop info for all the next few elements within the hop range
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

/**
 * Clears/Resets all the slots in our hashtable to their original state.
 * All occupancies would be set to false & the hopInfo bitmaps set to 0
 */
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::clear() {
    for (auto& bucket : hashTable) {
        bucket.occupied = false;
        bucket.hopInfo = 0;
    }
}

/**
 * The following method traverses through our hashtable and counts the number of buckets that are occupied
 * @return an integer indicating the number of occupied slots in our hashtable
 */
template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::size() const {
    unsigned int count = 0;
    // For each bucket in the hashtable, count up if it is occupied
    for (Bucket bucket : hashTable) {
        if (bucket.occupied) {
            ++count;
        }
    }
    return count;
}

/**
 * calculates the loadfactor of our hashtable = (# of elements)/tableSize
 * @return a double indicating the loadfactor
 */
template<typename KeyType, typename ValueType>
double HashTable<KeyType, ValueType>::loadFactor() const {
    return static_cast<double>(size()) / static_cast<double>(tableSize);
}


/**
 * Finds a free slot using linear probing
 * @param cTable the existing hashtable
 * @param startIndex the index we are finding a free slot from
 * @param currentHop
 * @return an Integer, representing the free slot we have found
 */
template<typename KeyType, typename ValueType>
unsigned int HashTable<KeyType, ValueType>::findFreeSlot(std::vector<Bucket>& cTable, unsigned int startIndex, unsigned int& currentHop) {
    unsigned int index = startIndex;
    for (unsigned int i = 0; i < tableSize; ++i) {
        if (!(cTable[index].occupied)) {
            currentHop = i;
            return index;
        }
        index = (index + 1) % tableSize;
    }
    return tableSize; // Indicates no free slot found
}

/**
 * Our rehash method if the loadfactor reaches beyond the set load factor.
 * We will double the size of our hashtable and restore the elements into our new table.
 */
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::rehash() {
    // Temporary storage for old table
    std::vector<Bucket> oldTable = hashTable;
    // double the size of the current table
    tableSize *= 2;
    hashTable.resize(tableSize);
    clear();

    // Re-insert elements into the new table
    for (Bucket bucket : oldTable) {
        if (bucket.occupied) {
            insert(bucket.key, bucket.value);
        }
    }
}

/**
 * The following code updates the value of an element in the hashtable given the key
 * @param key key element we want to set the new value for
 * @param newValue new value that is being inserted into th
 */
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


/**
 * Hash function to generate a hashkey given a key
 * @param key a Generic object type of key
 * @return an Integer Hash Key
 */
template<typename KeyType>
size_t hashKey(const KeyType& key) {

    std::stringstream ss;
    ss << key; // Convert key to a string representation using the << operator
    std::string str = ss.str(); // Convert the string representation to a string

    unsigned long i = 0;

    for (char ch : str) // Iterate over each string
        i += ch;

    return i;
}
