// C++ program for different tree traversals
#include <bits/stdc++.h>
using namespace std;

// A binary tree node has data, pointer to left child
// and a pointer to right child
struct Node {
    int data;
    struct Node *left, *right;
};

// Utility function to create a new tree node
Node* newNode(int data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

void insertNode(Node *currentNode, Node *newNode) {

    if (newNode == NULL || newNode->data == currentNode->data) {
        return;
    }

    if (currentNode->data < newNode->data) {
        if (currentNode->right == NULL) {
            currentNode->right = newNode;
        }
        insertNode(currentNode->right, newNode);
    }

    if (currentNode->data > newNode->data) {
        if (currentNode->left == NULL) {
            currentNode->left = newNode;
        }
        insertNode(currentNode->left, newNode);
    }
}


bool contains(Node *currentNode, Node *containsNode) {
    if (currentNode == NULL) {
        return false;
    }

    if (currentNode->data == containsNode->data) {
        return true;
    }

    if (containsNode->data > currentNode->data) {
        return contains(currentNode->right, containsNode);
    } else {
        return contains(currentNode->left, containsNode);
    }
}

// Given a binary tree, print its nodes in inorder
void printInorder(struct Node* node)
{
    if (node == NULL)
        return;

    // First recur on left child
    printInorder(node->left);

    // Then print the data of node
    cout << node->data << " ";

    // Now recur on right child
    printInorder(node->right);
}

// Driver code
int main()
{
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    // Function call
    cout << "Inorder traversal of binary tree is \n";
    printInorder(root);


    struct Node* comparingNode = newNode(3);
    cout << "Tree contains " << comparingNode->data << "?" << endl;
    cout << contains(root, comparingNode);
    return 0;
}
