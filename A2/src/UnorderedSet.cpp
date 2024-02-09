//
// Created by Sepeh on 2024-02-07.
//

#include "../include/UnorderedSet.h"


template<typename Key>
UnorderedSet<Key>::UnorderedSet() {
    root = nullptr;

}

template<typename Key>
UnorderedSet<Key>::~UnorderedSet() {
    root = nullptr;

}

template<typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::end() const {
    return UnorderedSet<Key>::Iterator(nullptr);
}

template<typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::begin() const {
    return UnorderedSet<Key>::Iterator(nullptr);
}


template<typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {

    if (root == nullptr) {
        root = new Node<Key>(key);
        root->color = Color::BLACK;
        return true;
    }

    if (root->key > key) {
        return insert(root->left);
    }

    if (root->key < key) {
        return insert(root->left);
    }
}

template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {
    return false;
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