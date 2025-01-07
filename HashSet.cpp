#include <iostream>
#include <vector>
#include <list>
using namespace std;

class HashSet {
private:
    vector<list<int>> table; // Hash table: vector of lists
    int capacity;            // Number of buckets
    int hash(int key) const {
        return key % capacity; // Simple hash function (modulus)
    }

public:
    // Constructor: initialize hash table with a fixed capacity
    HashSet(int cap = 10) : capacity(cap), table(cap) {}

    // Insert a key into the HashSet
    void insert(int key) {
        int index = hash(key); // Get the bucket index
        for (int element : table[index]) {
            if (element == key) {
                return; // Key already exists, no duplicates allowed
            }
        }
        table[index].push_back(key); // Add key to the bucket
    }

    // Remove a key from the HashSet
    void remove(int key) {
        int index = hash(key); // Get the bucket index
        table[index].remove(key); // Remove the key from the list
    }

    // Check if a key exists in the HashSet
    bool contains(int key) const {
        int index = hash(key); // Get the bucket index
        for (int element : table[index]) {
            if (element == key) {
                return true; // Key found
            }
        }
        return false; // Key not found
    }

    // Print the HashSet
    void print() const {
        for (int i = 0; i < capacity; ++i) {
            cout << "Bucket " << i << ": ";
            for (int element : table[i]) {
                cout << element << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashSet hashSet;

    hashSet.insert(10);
    hashSet.insert(20);
    hashSet.insert(15);
    hashSet.insert(25);
    hashSet.insert(35);

    cout << "HashSet contents after insertion:" << endl;
    hashSet.print();

    cout << "\nDoes HashSet contain 15? " << (hashSet.contains(15) ? "Yes" : "No") << endl;
    cout << "Does HashSet contain 40? " << (hashSet.contains(40) ? "Yes" : "No") << endl;

    hashSet.remove(15);
    cout << "\nHashSet contents after removing 15:" << endl;
    hashSet.print();

    return 0;
}
