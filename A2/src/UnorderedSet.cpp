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
        root->color = Color::BLACK;
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
        // If parent is Null, means it is the root. Therefore turn it to Black.
        if (parent == nullptr) {
            child->color = Color::BLACK;
            root = child;
        } else if (parent->left == nodeToDelete) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete nodeToDelete;
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
void UnorderedSet<Key>::fixRedRedViolation(Node<Key>* node) {
    while (node != root && node->parent->color == Color::RED) {
        Node<Key>* parent = node->parent;
        Node<Key>* grandparent = parent->parent;

        // Case 1: Parent is a left child of grandparent
        if (parent == grandparent->left) {
            Node<Key>* uncle = grandparent->right;

            // Case 1a: Uncle is also red, recoloring
            if (uncle != nullptr && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                // Case 1b: Uncle is black or null, rotation needed
                if (node == parent->right) {
                    // Case 1b-i: Node is a right child, left rotation needed
                    node = parent;
                    rotateLeft(node);
                    parent = node->parent;
                }

                // Case 1b-ii: Node is a left child, right rotation needed
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(grandparent);
            }
        } else { // Case 2: Parent is a right child of grandparent (symmetrical to case 1)
            Node<Key>* uncle = grandparent->left;

            // Case 2a: Uncle is also red, recoloring
            if (uncle != nullptr && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                // Case 2b: Uncle is black or null, rotation needed
                if (node == parent->left) {
                    // Case 2b-i: Node is a left child, right rotation needed
                    node = parent;
                    rotateRight(node);
                    parent = node->parent;
                }

                // Case 2b-ii: Node is a right child, left rotation needed
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color = Color::BLACK; // Ensure root is always black
}

template<typename Key>
void UnorderedSet<Key>::rotateLeft(Node<Key>* node) {
    Node<Key>* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

// Rotate Right operation
template<typename Key>
void UnorderedSet<Key>::rotateRight(Node<Key>* node) {
    Node<Key>* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == nullptr) {
        root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}


template<typename Key>
void UnorderedSet<Key>::deleteOneChild(Node<Key>* node) {
}

template<typename Key>
void UnorderedSet<Key>::deleteFix(Node<Key>* node) {
}

template<typename Key>
void UnorderedSet<Key>::clearRecursive(Node<Key> *node) {

}