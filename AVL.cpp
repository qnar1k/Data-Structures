#include <iostream>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	int height;
	Node(int value) {
		key = value;
		left = right = nullptr;
		height = 1;
	}
};
int getHeight(Node* node) {
	return node ? node->height : 0;
}
int getBalance(Node* node) {
	return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
void updateHeight(Node* node) {
	if (node) {
		node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	}
}
bool isBalanced(Node* root) {
    if (!root) return true;

    int balance = getBalance(root);
    return (balance >= -1 && balance <= 1) && isBalanced(root->left) && isBalanced(root->right);
}
//LL rotation
Node* rightRotate(Node* disbalancedNode) {
	Node* newRoot = disbalancedNode->left;
	disbalancedNode->left = disbalancedNode->left->right;
	newRoot->right = disbalancedNode; 

	updateHeight(disbalancedNode);
	updateHeight(newRoot);

	return newRoot;
}
Node* leftRotate(Node* disbalancedNode) {
	Node* newRoot = disbalancedNode->right;
	disbalancedNode->right = disbalancedNode->right->left;
	newRoot->left = disbalancedNode; 

	updateHeight(disbalancedNode); 
	updateHeight(newRoot);

	return newRoot;
}
// Insert a new node to the AVL tree
Node* insert(Node* root, int key) {
    // Perform normal BST insertion
    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // Duplicates are not allowed in AVL Tree
        return root;

    // Update the height of this ancestor node
    updateHeight(root);

    // Get the balance factor to check if the node became unbalanced
    int balance = getBalance(root);

    // If the node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the (unchanged) node pointer
    return root;
}
// Inorder traversal to print the tree
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}
void preorder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(Node* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }
}
