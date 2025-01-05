#include <iostream>
#include <stdexcept>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insertHelper(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* findMax(Node* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    Node* deleteHelper(Node* node, int value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data);
        }
        return node;
    }

    void inOrderTraversal(Node* node) {
        if (node == nullptr) return;
        inOrderTraversal(node->left);
        cout << node->data << " ";
        inOrderTraversal(node->right);
    }

    void preOrderTraversal(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }

    // Helper function for post-order traversal
    void postOrderTraversal(Node* node) {
        if (node == nullptr) return;
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->data << " ";
    }

    bool searchHelper(Node* node, int value) {
        if (node == nullptr) return false;
        if (node->data == value) return true;
        if (value < node->data) {
            return searchHelper(node->left, value);
        }
        else {
            return searchHelper(node->right, value);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(int value) {
        root = insertHelper(root, value);
    }

    int findMinValue() {
        if (root == nullptr) {
            throw runtime_error("The tree is empty!");
        }
        return findMin(root)->data;
    }

    int findMaxValue() {
        if (root == nullptr) {
            throw runtime_error("The tree is empty!");
        }
        return findMax(root)->data;
    }

    void deleteValue(int value) {
        root = deleteHelper(root, value);
    }

    bool search(int value) {
        return searchHelper(root, value);
    }

    void inOrder() {
        inOrderTraversal(root);
        cout << endl;
    }

    void preOrder() {
        preOrderTraversal(root);
        cout << endl;
    }

    void postOrder() {
        postOrderTraversal(root);
        cout << endl;
    }
};

int main() {
    BST tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "In-order Traversal: ";
    tree.inOrder(); 

    cout << "Pre-order Traversal: ";
    tree.preOrder(); 

    cout << "Post-order Traversal: ";
    tree.postOrder(); 

    cout << "Minimum value in the BST: " << tree.findMinValue() << endl; 
    cout << "Maximum value in the BST: " << tree.findMaxValue() << endl; 

    int searchValue = 40;
    cout << "Is " << searchValue << " present in the BST? "
        << (tree.search(searchValue) ? "Yes" : "No") << endl;

    cout << "Deleting 70...\n";
    tree.deleteValue(70);
    cout << "In-order Traversal after deletion: ";
    tree.inOrder(); 

    return 0;
}

