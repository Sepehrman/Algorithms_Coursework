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


    Node<Key>* parent = nullptr;
    Node<Key>* current = root;
    while (current != nullptr) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else { // Key already exists
            return false;
        }
    }

    Node<Key> *newNode = new Node<Key>(key);

    newNode->parent = parent;
    if (parent == nullptr)
        root = newNode;
    else if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    ++setSize;

//    fixRedRedViolation(newNode);

    return true;
}

template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {

    if (root->key == key) {
        return true;
    }

    Node<Key>* current = root;

    while (current != nullptr) {
        if (current->key < key) {
            current = current->left;
        } else if (current->key > key) {
            current = current->right;
        } else {
            return true;
        }
    }

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