#include <iostream>
#include <stdexcept>
using namespace std;
template<typename T>
struct Node {
	T value;
	Node* next;
	Node(T value, Node* next) : value(value), next(next) {}
	Node(T value) : value(value), next(nullptr) {}
	Node() : value(0), next(nullptr) {}
};
template<typename T>
class List {
public:
	Node<T>* head;
	Node<T>* tail;
	int count;
	List() : head(nullptr), tail(nullptr), count(0) {}

	bool isEmpty() {
		return (count == 0);
	}


	void insertAtHead(T value) {
		Node<T>* newNode = new Node<T>(value); 
		if (isEmpty()) {
			head = tail = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
		count++;
	}
	void insertAtTail(T value) {
		Node<T> newNode = new Node<T>(value);
		if (isEmpty()) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	}
	void insertAtPosition(T value, int i) {
		if (i <= 0 || i > count + 1) {
			throw out_of_range("Invalid position");
		}
		Node<T>* newNode = new Node<T>(value);
		Node<T>* temp = head;
		if (i == 1) {
			insertAtHead(value);
			return;
		}
		if (i == count + 1) {
			insertAtTail(value);
			return;
		}
		while (--i > 1) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
		count++;
	}
	void deleteAtHead() {
		if (isEmpty()) {
			throw out_of_range("List is empty. Cannot delete from an empty list.");
		}
		Node<T>* temp = head;
		head = head->next;
		delete temp;
		if (head == nullptr) {
			tail = nullptr;
		}
		count--;
	}
	void deleteAtTail() {
		if (isEmpty()) {
			throw out_of_range("List is empty. Cannot delete from an empty list.");
		}
		if (head == tail) {
			delete head;
			head = tail = nullptr;
		}
		else {
			Node<T>* temp = head;
			while (temp->next->next) {
				temp = temp->next;
			}
			delete tail;
			tail = temp;
			temp->next = nullptr;
		}
		count--;
	}
	void deleteAtPosition(int i) {
		if (i <= 0 || i > count + 1) {
			throw out_of_range("Invalid position");
		}
		if (isEmpty()) {
			throw out_of_range("List is empty. Cannot delete from an empty list.");
		}
		if (i == 1) {
			deleteAtHead();
			return;
		}
		if (i == count) {
			deleteAtTail();
			return;
		}
		Node<T>* temp = head;
		while (--i > 1) {
			temp = temp-> next;
		}
		Node<T>* temp1 = temp->next;
		temp->next = temp->next->next;
		if (temp->next == nullptr) {
			tail = temp;
		}
		delete temp1;
		count--;
	}
	void display() const {
		Node<T>* temp = head;
		while (temp) {
			cout << temp->value << " -> ";
			temp = temp->next;
		}
		cout << "nullptr" << endl;
	}
};
