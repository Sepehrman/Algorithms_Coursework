//
// Created by Sepeh on 2024-02-02.
//


#include "../include/UnorderedSet.h"


template<typename Key>
UnorderedSet<Key>::UnorderedSet() {

}

template<typename Key>
UnorderedSet<Key>::~UnorderedSet() {

}

template<typename Key>
UnorderedSet::Iterator UnorderedSet<Key>::begin() const {
    return UnorderedSet::Iterator(nullptr);
}

template<typename Key>
UnorderedSet::Iterator UnorderedSet<Key>::end() const {
    return UnorderedSet::Iterator(nullptr);
}

template<typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {
    return false;
}

template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {

}

template<typename Key>
bool UnorderedSet<Key>::erase(const Key &key) {
    return false;
}

template<typename Key>
void UnorderedSet<Key>::clear() {

}

template<typename Key>
size_t UnorderedSet<Key>::size() const {
    return 0;
}

template<typename Key>
void UnorderedSet<Key>::updateSize() {

}

template<typename Key>
size_t UnorderedSet<Key>::getSize(Node<Key> *node) const {
    return 0;
}

template<typename Key>
void UnorderedSet<Key>::fixRedRedViolation(Node<Key> *node) {

}

template<typename Key>
void UnorderedSet<Key>::rotateLeft(Node<Key> *node) {

}

template<typename Key>
void UnorderedSet<Key>::rotateRight(Node<Key> *node) {

}

template<typename Key>
void UnorderedSet<Key>::deleteOneChild(Node<Key> *node) {

}

template<typename Key>
void UnorderedSet<Key>::deleteFix(Node<Key> *node) {

}

template<typename Key>
void UnorderedSet<Key>::clearRecursive(Node<Key> *node) {

}