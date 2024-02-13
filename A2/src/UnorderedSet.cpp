/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/UnorderedSet.h"

using namespace std;

/*
 * A constructor for our Unordered Red-Black-Tree Set
 */
template<typename Key>
UnorderedSet<Key>::UnorderedSet() {
    root = nullptr;
    setSize = 0;
}

/*
 * A destructor for our Unordered Red-Black-Tree Set
 */
template<typename Key>
UnorderedSet<Key>::~UnorderedSet() {
    clear();
}

/**
 * This method returns the left-most element of our tree until until-before it reaches a nullptr
 * @tparam Key a Generic parameter of Type Key
 * @return an Iterator
 */
template<typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::begin() const {
//    return UnorderedSet<Key>::Iterator(root);
    Node<Key>* current = root;
    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }
    return Iterator(current);
}

/**
 * This method returns the end of our tree until until-before, signifying past the last element which is a nullptr
 * @tparam Key a Generic parameter of Type Key
 * @return an Iterator
 */
template<typename Key>
typename UnorderedSet<Key>::Iterator UnorderedSet<Key>::end() const {
    return UnorderedSet<Key>::Iterator(nullptr);
}

/**
 * The following method is responsible for adding a Key element to our Tree.
 * @tparam Key a Generic parameter of Type Key
 * @param key An object of type Key that we are planning to insert into our tree
 * @return a Boolean; indicating whether the item already exists or not
 */
template<typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {

    // TODO: Add what code does
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
    } else {
        newNode->color = Color::RED;
        parent->right = newNode;
    }

    ++setSize;

    if (newNode->color == Color::RED && newNode->parent->color == Color::RED) {
        fixRedRedViolation(newNode);
    }

    return true;
}

template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {

    if (root->key == key) {
        return true;
    }

    Node<Key>* current = root;

    while (current != nullptr) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
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
    Node<Key> *parent = nullptr;
    Node<Key> *nodeToDelete = nullptr;

    // Search for the node to delete
    while (current != nullptr) {
        if (key < current->key) {
            parent = current;
            current = current->left;
        } else if (key > current->key) {
            parent = current;
            current = current->right;
        } else {
            nodeToDelete = current;
            break;
        }
    }

    if (nodeToDelete == nullptr) {
        return false;
    }

    // Case 1: Node to delete has no children
    if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
        if (parent == nullptr) {
            root = nullptr;
        } else if (parent->left == nodeToDelete) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete nodeToDelete;
    }

        // Case 2: Node to delete has one child
    else if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
        Node<Key> *child = (nodeToDelete->left != nullptr) ? nodeToDelete->left : nodeToDelete->right;
        if (parent == nullptr) {
            // Node to delete is the root
            root = child;
        } else if (parent->left == nodeToDelete) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete nodeToDelete;

        // If the node to delete has no child, simply delete it
        // If it has one child, the child takes its place, so we delete the nodeToDelete
    }

        // Case 3: Node to delete has two children
    else {
        Node<Key> *successor = nodeToDelete->right;
        parent = nullptr;
        while (successor->left != nullptr) {
            parent = successor;
            successor = successor->left;
        }

        // Replace nodeToDelete with successor
        nodeToDelete->key = successor->key;

        // Delete the successor node
        if (parent != nullptr) {
            parent->left = nullptr;
        } else {
            nodeToDelete->right = nullptr;
        }
        delete successor;
    }

    --setSize;
    return true;
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

    Node<Key> *father = node->parent;
    Node<Key> *grandFather = father->parent;
    Node<Key> *uncle = grandFather->left != father ? grandFather->left : grandFather->right;
    Node<Key> *currentNode = node;

    // Case 1: if uncle is Red, switch the color of
    if (uncle == nullptr || uncle->color == Color::BLACK) {

        // if is Left-Left
        if (grandFather->left != nullptr && grandFather->left->left == node) {
            rotateRight(node->parent);
        }
        // if Right-Right
        else if (grandFather->right != nullptr && grandFather->right->right == node) {
            rotateLeft(node->parent);
        }
        // if Right-Left
        else if (grandFather->right != nullptr && grandFather->right->left == node) {
            // Perform appropriate rotations here
        }
        // If Left-Right
        else if (grandFather->left != nullptr && grandFather->left->right == node) {
            // Perform appropriate rotations here
        }

    } else if (uncle->color == Color::RED) {
        uncle->color = Color::BLACK;
        father->color = Color::BLACK;
    }
//    if (uncle == nullptr)


}

template<typename Key>
void UnorderedSet<Key>::rotateLeft(Node<Key> *node) {
    if (node == nullptr || node->right == nullptr)
        return; // Cannot rotate if the node or its right child is null

    Node<Key> *pivot = node->right;
    node->right = pivot->left;
    if (pivot->left != nullptr)
        pivot->left->parent = node;
    pivot->parent = node->parent;
    if (node->parent == nullptr)
        root = pivot;
    else if (node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;
    pivot->left = node;
    node->parent = pivot;
}

template<typename Key>
void UnorderedSet<Key>::rotateRight(Node<Key> *node) {
    if (node == nullptr || node->left == nullptr)
        return; // Cannot rotate if the node or its left child is null

    Node<Key> *pivot = node->left;
    node->left = pivot->right;
    if (pivot->right != nullptr)
        pivot->right->parent = node;
    pivot->parent = node->parent;
    if (node->parent == nullptr)
        root = pivot;
    else if (node == node->parent->left)
        node->parent->left = pivot;
    else
        node->parent->right = pivot;
    pivot->right = node;
    node->parent = pivot;
}

template<typename Key>
void UnorderedSet<Key>::deleteOneChild(Node<Key> *node) {

    Node<Key> *temp = node;
    Node<Key> *parent = node->parent;
}

template<typename Key>
void UnorderedSet<Key>::deleteFix(Node<Key> *node) {

}

template<typename Key>
void UnorderedSet<Key>::clearRecursive(Node<Key> *node) {

}