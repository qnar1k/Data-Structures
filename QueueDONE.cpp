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
class Queue {
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    bool isEmpty() const{
        return (count == 0);
    }

    int size() const {
        return count;
    }

    T peek() const {
        if (isEmpty()) {
            throw out_of_range("Queue is empty: No top element to peek.");
        }
        return head->data; 
    }

    void enqueue(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = nullptr;
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            throw out_of_range("Queue underflow: Cannot dequeue from an empty queue.");
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        count--;

        if (!head) {
            tail = nullptr; 
        }
    }
    void display() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl; 
    }
};
