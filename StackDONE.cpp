#include <iostream>
#include <stdexcept>  
using namespace std; 

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
class Stack {
    Node<T>* top;
    int count;

public:
    Stack() : count(0), top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();  
        }
    }

    void push(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = top;
        top = newNode;
        count++;
    }

    void pop() {
        if (isEmpty()) {
            throw out_of_range("Stack underflow: Cannot pop from an empty stack.");
        }
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        count--;
    }

    T peek() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty: No top element to peek.");
        }
        return top->data;
    }

    bool isEmpty() const {
        return (count == 0);
    }

    int size() const {
        return count;
    }

    void display() const {
        Node<T>* current = top;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
};
