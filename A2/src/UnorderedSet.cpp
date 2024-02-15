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
 * @return a Boolean; indicating whether the item can be inserted or not (If the item exists)
 */
template<typename Key>
bool UnorderedSet<Key>::insert(const Key &key) {

    /* The following code starts from the root of our tree and goes down, based on whether our inserted key is
     * higher (right) or lower (left) than the root. If upon searching we find the existing key, returns false.
     */
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


    /* Creates a new Node to insert to the tree. If the tree's parent is null, it is assumed to be the root and sets
     * the root as the new node, coloring it Black. If the key is smaller than or larger than the key's parent,
     * sets the node on the left or right accordingly and colors it Red.
     */
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

    // Increases the size of the tree by 1
    ++setSize;

    /* Checks whether there are any red-red violations once the new node is added.
     * Ensures that the root always remains Black.
    */
     if (newNode->color == Color::RED && newNode->parent->color == Color::RED) {
        fixRedRedViolation(newNode);
        root->color = Color::BLACK;
    }
    return true;
}

/**
 * Searches the entire tree for a given key and returns whether it exists, or not.
 * @tparam Key a Generic parameter of Type Key
 * @param key An object of type Key; The key we are searching for
 * @return a Boolean; Based on whether the key is found or not in the tree
 */
template<typename Key>
bool UnorderedSet<Key>::search(const Key &key) const {

    // If the root equals the key, return true.
    if (root->key == key) {
        return true;
    }

    /* Sets current node position to start from the root and goes down the tree until it reaches a null pointer.
     * Changes the current node to the left or right child accordingly. If the current node equals the key, returns true.
     */
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

    // Once the node reaches a null pointer, it moves out of the while loop and returns a false.
    return false;
}


/**
 * The following method erases a key from our Tree
 * @tparam Key a Generic parameter of Type Key
 * @param key the key we would like to remove.
 * @return a Boolean; Whether the key was successfully removed or not (i.e could not be found)
 */
template<typename Key>
bool UnorderedSet<Key>::erase(const Key &key) {
    Node<Key> *current = root;
    Node<Key> *parent = nullptr;
    Node<Key> *nodeToDelete = nullptr;

    // Search for the node to delete and find it.
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

    // If the node to delete does not exist, return false
    if (nodeToDelete == nullptr) {
        return false;
    }

    // If the Node to delete has no children
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

    // If the Node to delete has one child
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

    // If Node to delete has two children
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

    // Decrease the size of tree by 1.
    --setSize;
    return true;
}


/**
 * The following method handles a fixture to any red-red violations occuring within our tree and modifies it accordingly
 * Through checking for Red or Black uncles and judging on whether there should only be a color-switch and a rotation
 * happening.
 * @tparam Key a Generic parameter of Type Key
 * @param node the newly added key we are trying to resolve
 */
template<typename Key>
void UnorderedSet<Key>::fixRedRedViolation(Node<Key>* node) {
    // Step 1: Check if the node is not the root and the parent's color is red
        Node<Key>* parent = node->parent;
        Node<Key>* grandparent = parent->parent;
        Node<Key>* uncle = grandparent->right;

        // Parent is a left child of grandparent
        if (parent == grandparent->left) {

            // Uncle is red, Only do color switch.
            if (uncle != nullptr && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;

                // Uncle is Black/Null, therefore do rotation & color switch
            } else {

                // Node is Right child, therefore do a single left rotation. (RR Case)
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(node);
                    parent = node->parent;
                }

                // Node is left child, do a right rotation (RL Case) and switches color of parent & grandparent
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(grandparent);
            }

            // Parent is a right child of grandparent
        } else {

            Node<Key>* uncle = grandparent->left;
            // Uncle is red, Only do color switch.
            if (uncle != nullptr && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;

            // Uncle is Black/Null, therefore do rotation & color switch
            } else {


                // Node is a left child, right rotation needed (RL Case)
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                    parent = node->parent;
                }

                // Node is a right child, left rotation needed. switches color of parent & grandparent
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(grandparent);
            }
        }
}

/**
 * The following function does a left rotation on a tree that has had a red-red violation
 * @tparam Key a Generic parameter of Type Key
 * @param node the basis of a node from the tree we want to rotate from
 */
template<typename Key>
void UnorderedSet<Key>::rotateLeft(Node<Key>* node) {
    //
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

/**
 * The following function does a right rotation on a tree that has had a red-red violation
 * @tparam Key a Generic parameter of Type Key
 * @param node the basis of a node from the tree we want to rotate from
 */
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

/**
 * Clears the current tree by setting the root to null & the size of the tree to 0.
 * @param node the basis of a node from the tree we want to rotate from
 */
template<typename Key>
void UnorderedSet<Key>::clear() {
    root = nullptr;
    setSize = 0;
}

/**
 * Gets the size of the current tree
 * @tparam Key a Generic parameter of Type Key
 * @return An Integer; representing the size of the tree.
 */
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
void UnorderedSet<Key>::deleteOneChild(Node<Key>* node) {
}

template<typename Key>
void UnorderedSet<Key>::deleteFix(Node<Key>* node) {
}

template<typename Key>
void UnorderedSet<Key>::clearRecursive(Node<Key> *node) {
}