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

    // TODO: Add implementation for parent node?
//    Node<Key>* currentNode = root;
//    Node<Key>* parent = nullptr;

    if (root == nullptr) {
        root = new Node<Key>(key);
        root->color = Color::BLACK;
        setSize++;
        return true;
    }

    if (key < root->key) {
        root = root->left;
        insert(key);
    }

    if (key > root->key) {
        root = root->right;
        insert(key);
    }

    return true;
}

template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {

    if (&key == nullptr) {
        return false;
    }

    if (root->key == key) {
        return true;
    }

    if (key < root->key) {
        root = root->left;
    }

    if (key > root->key) {
        root = root->right;
    }
    search(key);
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