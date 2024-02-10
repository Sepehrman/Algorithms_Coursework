//
// Created by Sepeh on 2024-02-07.
//

#include "../include/UnorderedSet.h"

using namespace std;

template<typename Key>
UnorderedSet<Key>::UnorderedSet() {
    root = nullptr;
    setSize = 0;
}

template<typename Key>
UnorderedSet<Key>::~UnorderedSet() {
    clear();
}

template<typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::begin() const {
    return UnorderedSet<Key>::Iterator(root);
}



template<typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::end() const {
    return UnorderedSet<Key>::Iterator(nullptr);
}


template<typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {


    if (root == nullptr) {
        root = new Node<Key>(key);
        root->color = Color::BLACK;
        setSize++;
        return true;
    }

    if (key < root->key) {
        root = root->left;
        insert(key);
        // WORKING SAMPLE
//        root->left = new Node<Key>(key);
//        root->left->parent = root;
//        return true;
    }

    if (key > root->key) {
        root = root->right;
    }

    return true;
//    if (root->key > key) {
//        root->left;
//        return insert();
//    }
//
//    if (root->key < key) {
//        return insert(root->left);
//    }
}

template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {

//    if (key == nullptr) {
//        return false;
//    }
//
//    if (key < root->key) {
//
//    }
//
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
    return setSize;
}

template<typename Key>
void UnorderedSet<Key>::updateSize() {

}

template<typename Key>
size_t UnorderedSet<Key>::getSize(Node<Key> *node) const {
    return setSize;
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