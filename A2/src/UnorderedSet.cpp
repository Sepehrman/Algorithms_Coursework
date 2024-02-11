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


    // TODO: Set colors for red/black trees
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
    if (parent == nullptr) {
        newNode->color = Color::BLACK;
        root = newNode;
    } else if (key < parent->key) {
        newNode->color = Color::RED;
        parent->left = newNode;
    }
    else {
        newNode->color = Color::RED;
        parent->right = newNode;
    }

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

    Node<Key> *current = root;
    Node<Key> *nodeToDelete = nullptr;


    // TODO: Handle if root node is deleted. Do a rotation?
    // TODO: Also consider the blue colors

    bool isFound = false;

    while (current != nullptr) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            isFound = true;
            nodeToDelete = current;
            break;
        }
    }

    if (isFound) {

//        if (nodeToDelete->color == Color::RED) {
//            // DELETE then exit.
//            return true;
//        } else if (nodeToDelete->color == Color::BLACK && nodeToDelete->left == nullptr && nodeToDelete->right== nullptr) {
//            nodeToDelete->key == nullptr;
//            nodeToDelete->color == Color::BLUE;
//        }
    }


    return isFound;


//    while (current->key)
}

template<typename Key>
void UnorderedSet<Key>::clear() {

    root = nullptr;
    setSize = 0;
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