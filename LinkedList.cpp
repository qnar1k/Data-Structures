#include <iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class ListNode {
public:
    T val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(T x) : val(x), next(nullptr) {}
    ListNode(T x, ListNode* next) : val(x), next(next) {}
};

template<typename T>
class List {
public:
    ListNode<T>* head;
    ListNode<T>* tail;
    int count;

    List() : head(nullptr), tail(nullptr), count(0) {}

    ~List() {
        while (head) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void insertAtHead(const T data) {
        ListNode<T>* newNode = new ListNode<T>(data);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }

    void insertAtTail(T data) {
        ListNode<T>* newNode = new ListNode<T>(data);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void insertAtPosition(int position, T data) {
        if (position <= 0 || position > count + 1) {
            throw out_of_range("Invalid position");
        }

        ListNode<T>* newNode = new ListNode<T>(data);
        if (position == 1) {
            insertAtHead(data);
            return;
        }

        ListNode<T>* temp = head;
        for (int i = 1; i < position - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        if (newNode->next == nullptr) {
            tail = newNode;
        }
        count++;
    }

    void deleteAtHead() {
        if (isEmpty()) {
            throw out_of_range("List is empty. Cannot delete from an empty list.");
        }
        ListNode<T>* temp = head;
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
            ListNode<T>* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        count--;
    }

    void deleteAtPosition(int position) {
        if (isEmpty()) {
            throw out_of_range("List is empty. Cannot delete from an empty list.");
        }

        if (position <= 0 || position > count) {
            throw out_of_range("Invalid position");
        }

        if (position == 1) {
            deleteAtHead();
            return;
        }

        ListNode<T>* temp = head;
        for (int i = 1; i < position - 1; i++) {
            temp = temp->next;
        }
        ListNode<T>* temp1 = temp->next;
        temp->next = temp->next->next;
        delete temp1;

        if (temp->next == nullptr) {
            tail = temp;
        }

        count--;
    }

    void display() const {
        ListNode<T>* temp = head;
        while (temp) {
            cout << temp->val << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    int size() const {
        return count;
    }
};

