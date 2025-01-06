#include <iostream>
#include <vector>
#include <list>
#include <functional>

class HashSet {
private:
    static const int DEFAULT_CAPACITY = 10;
    static constexpr float LOAD_FACTOR = 0.75;

    std::vector<std::list<int>> table;
    int size;

    int hash(int value) const {
        return std::hash<int>()(value) % table.size();
    }

    void rehash() {
        std::vector<std::list<int>> oldTable = table;
        table.resize(table.size() * 2);
        for (auto& bucket : table) {
            bucket.clear();
        }
        size = 0;

        for (const auto& bucket : oldTable) {
            for (int value : bucket) {
                add(value);
            }
        }
    }

public:
    HashSet() : table(DEFAULT_CAPACITY), size(0) {}

    void add(int value) {
        int index = hash(value);
        auto& bucket = table[index];

        for (int existingValue : bucket) {
            if (existingValue == value) {
                return; // Element already exists
            }
        }

        bucket.push_back(value);
        ++size;

        if (size > LOAD_FACTOR * table.size()) {
            rehash();
        }
    }

    bool contains(int value) const {
        int index = hash(value);
        const auto& bucket = table[index];

        for (int existingValue : bucket) {
            if (existingValue == value) {
                return true;
            }
        }
        return false;
    }

    void remove(int value) {
        int index = hash(value);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == value) {
                bucket.erase(it);
                --size;
                return;
            }
        }
    }

    void printSet() const {
        for (size_t i = 0; i < table.size(); ++i) {
            if (!table[i].empty()) {
                std::cout << "Bucket " << i << ": ";
                for (int value : table[i]) {
                    std::cout << value << " ";
                }
                std::cout << "\n";
            }
        }
    }
};

int main() {
    HashSet hashSet;

    hashSet.add(5);
    hashSet.add(10);
    hashSet.add(15);
    hashSet.add(20);

    std::cout << "Set after adding elements:\n";
    hashSet.printSet();

    std::cout << "Contains 10? " << (hashSet.contains(10) ? "Yes" : "No") << "\n";
    std::cout << "Contains 25? " << (hashSet.contains(25) ? "Yes" : "No") << "\n";

    hashSet.remove(10);
    std::cout << "Set after removing 10:\n";
    hashSet.printSet();

    return 0;
}
