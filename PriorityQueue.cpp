
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class PriorityQueue {
private:
    vector<int> heap;
    bool isMinHeap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        while (index > 0 && compare(heap[index], heap[parent(index)])) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        int smallestOrLargest = index;

        int left = leftChild(index);
        int right = rightChild(index);

        if (left < size && compare(heap[left], heap[smallestOrLargest]))
            smallestOrLargest = left;

        if (right < size && compare(heap[right], heap[smallestOrLargest]))
            smallestOrLargest = right;

        if (smallestOrLargest != index) {
            swap(heap[index], heap[smallestOrLargest]);
            heapifyDown(smallestOrLargest);
        }
    }

    bool compare(int a, int b) {
        return isMinHeap ? a < b : a > b;
    }

public:
    PriorityQueue(bool minHeap = true) : isMinHeap(minHeap) {}

    void push(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) {
            throw runtime_error("Priority Queue is empty!");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    int top() {
        if (heap.empty()) {
            throw runtime_error("Priority Queue is empty!");
        }
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

    void printQueue() {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "Min-Heap Priority Queue:\n";
    PriorityQueue minQueue(true); // Min-Heap
    minQueue.push(10);
    minQueue.push(30);
    minQueue.push(20);
    minQueue.push(5);

    cout << "Priority Queue: ";
    minQueue.printQueue();
    cout << "Top Element: " << minQueue.top() << "\n";
    minQueue.pop();
    cout << "After Pop: ";
    minQueue.printQueue();

    cout << "\nMax-Heap Priority Queue:\n";
    PriorityQueue maxQueue(false); // Max-Heap
    maxQueue.push(10);
    maxQueue.push(30);
    maxQueue.push(20);
    maxQueue.push(5);

    cout << "Priority Queue: ";
    maxQueue.printQueue();
    cout << "Top Element: " << maxQueue.top() << "\n";
    maxQueue.pop();
    cout << "After Pop: ";
    maxQueue.printQueue();

    return 0;
}
