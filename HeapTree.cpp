#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Heap {
private:
    vector<int> heapArray;
    bool isMinHeap; 

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        while (index > 0 && compare(heapArray[index], heapArray[parent(index)])) {
            swap(heapArray[index], heapArray[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int size = heapArray.size();
        int smallestOrLargest = index;

        int left = leftChild(index);
        int right = rightChild(index);

        if (left < size && compare(heapArray[left], heapArray[smallestOrLargest]))
            smallestOrLargest = left;
        if (right < size && compare(heapArray[right], heapArray[smallestOrLargest]))
            smallestOrLargest = right;

        if (smallestOrLargest != index) {
            swap(heapArray[index], heapArray[smallestOrLargest]);
            heapifyDown(smallestOrLargest);
        }
    }

    bool compare(int a, int b) {
        return isMinHeap ? a < b : a > b;
    }

public:
    Heap(bool minHeap = true) : isMinHeap(minHeap) {}

    void insert(int value) {
        heapArray.push_back(value);
        heapifyUp(heapArray.size() - 1);
    }

    void deleteRoot() {
        if (heapArray.empty()) {
            cout << "Heap is empty!" << endl;
            return;
        }

        heapArray[0] = heapArray.back();
        heapArray.pop_back();

        heapifyDown(0);
    }

    void printHeap() {
        cout << "Heap elements: ";
        for (int val : heapArray) {
            cout << val << " ";
        }
        cout << endl;
    }
};

int main() {
    cout << "Max-Heap Example:" << endl;
    Heap maxHeap(false); 
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(30);

    maxHeap.printHeap(); 
    maxHeap.deleteRoot();
    maxHeap.printHeap(); 

    cout << "\nMin-Heap Example:" << endl;
    Heap minHeap(true);
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(5);
    minHeap.insert(30);

    minHeap.printHeap(); 
    minHeap.deleteRoot();
    minHeap.printHeap(); 

    return 0;
}

