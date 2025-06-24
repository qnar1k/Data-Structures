#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
using namespace std;

class HashTable {
private:
    int capacity;
    int count;  // Number of key-value pairs stored
    double loadFactorThreshold;
    vector<list<pair<int, int>>> table;

public:
    // Optional default constructor
    HashTable(int cap = 16, double loadThreshold = 0.75)
        : capacity(cap), count(0), loadFactorThreshold(loadThreshold), table(cap) {}

    int HashFunction(int key) const {
        return key % capacity;
    }

    void insert(int key, int value) {
        int index = HashFunction(key);
        for (auto& element : table[index]) {
            if (element.first == key) {
                element.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        count++;

        if ((double)count / capacity > loadFactorThreshold) {
            rehash();
        }
    }

    int search(int key) const {
        int index = HashFunction(key);
        for (const auto& element : table[index]) {
            if (element.first == key) {
                return element.second;
            }
        }
        throw runtime_error("Key not found");
    }

    int get(int key) const {
        return search(key);
    }

    bool remove(int key) {
        int index = HashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                count--;
                return true;
            }
        }
        return false;
    }

    bool contains(int key) const {
        int index = HashFunction(key);
        for (const auto& element : table[index]) {
            if (element.first == key) return true;
        }
        return false;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void display() const {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            if (table[i].empty()) {
                cout << "Empty";
            } else {
                for (const auto& element : table[i]) {
                    cout << "[" << element.first << ": " << element.second << "] ";
                }
            }
            cout << endl;
        }
    }

    void rehash() {
        int new_capacity = capacity * 2;
        vector<list<pair<int, int>>> new_table(new_capacity);

        for (int i = 0; i < capacity; ++i) {
            for (const auto& element : table[i]) {
                int new_index = element.first % new_capacity;
                new_table[new_index].emplace_back(element);
            }
        }

        table = move(new_table);
        capacity = new_capacity;
        // count stays the same
    }
};
