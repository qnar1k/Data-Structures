#include <iostream>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int val) : left(nullptr), right(nullptr), data(val) {}

};
class BinaryTree {
private:
	Node* root;
	Node* insertHelper(Node* node, int value) {
		if (node == nullptr) {
			return new Node(value);
		}
		if (value < node->data) {
			node->left = insertHelper(node->left, value);
		}
		else {
			node->right = insertHelper(node->right, value);
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
	void postOrderTraversal(Node* node) {
		if (node == nullptr) return;
		postOrderTraversal(node->left);
		postOrderTraversal(node->right);
		cout << node->data << " ";
	}
public:
	BinaryTree() : root(nullptr) {}

	// Insert function
	void insert(int value) {
		root = insertHelper(root, value);
	}

	// Traversals
	void inOrder() {
		inOrderTraversal(root);
		std::cout << std::endl;
	}

	void preOrder() {
		preOrderTraversal(root);
		std::cout << std::endl;
	}

	void postOrder() {
		postOrderTraversal(root);
		std::cout << std::endl;
	}
	int height(Node* node) {
		if (node == nullptr) return 0;
		int leftHeight = height(node->left);
		int rightHeight = height(node->right);
		return 1 + std::max(leftHeight, rightHeight);
	}
	int countNodes(Node* node) {
		if (node == nullptr) return 0;
		return 1 + countNodes(node->left) + countNodes(node->right);
	}
	bool isBalanced(Node* node) {
		if (node == nullptr) return true;
		int leftHeight = height(node->left);
		int rightHeight = height(node->right);
		return abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
	}
};
int main() {
	BinaryTree tree;

	tree.insert(10);
	tree.insert(5);
	tree.insert(15);
	tree.insert(3);
	tree.insert(7);

	std::cout << "In-order Traversal: ";
	tree.inOrder();

	std::cout << "Pre-order Traversal: ";
	tree.preOrder();

	std::cout << "Post-order Traversal: ";
	tree.postOrder();

	return 0;
}



