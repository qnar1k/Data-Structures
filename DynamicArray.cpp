#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Array {
private:
    T* ptr;
    int size;
public:
    Array(int size1)
        : size{ (size1 > 0 ? size1 : (throw invalid_argument{"Array size must be greater than 0"})) },
        ptr{ new T[size1] } {}

    Array(const Array& right)
        : size{ right.size }, ptr{ new T[right.size] } {
        for (int i = 0; i < size; i++) {
            ptr[i] = right.ptr[i];
        }
    }

    ~Array() {
        delete[] ptr;
        ptr = nullptr;
    }

    int getSize() const { return size; }

    const Array& operator=(const Array& right) {
        if (this != &right) {
            if (size != right.size) {
                delete[] ptr;
                size = right.size;
                ptr = new T[size];
            }
            for (int i = 0; i < size; i++) {
                ptr[i] = right.ptr[i];
            }
        }
        return *this;
    }

    Array& operator=(Array&& right) noexcept {
        if (this != &right) {
            delete[] ptr;
            ptr = right.ptr;
            size = right.size;
            right.ptr = nullptr;
            right.size = 0;
        }
        return *this;
    }

    bool operator==(const Array& arr) const {
        if (size != arr.size) return false;
        for (int i = 0; i < size; i++) {
            if (ptr[i] != arr.ptr[i]) return false;
        }
        return true;
    }

    T& operator[](const int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return ptr[index];
    }

    int length() const { return size; }

    void resize(int newSize) {
        if (newSize <= 0) {
            throw invalid_argument("New size must be positive");
        }
        T* newPtr = new T[newSize];
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; ++i) {
            newPtr[i] = ptr[i];
        }
        delete[] ptr;
        ptr = newPtr;
        size = newSize;
    }

    friend ostream& operator<<(ostream& out, const Array& arr) {
        for (int i = 0; i < arr.size; i++) {
            out << arr.ptr[i] << " ";
        }
        return out;
    }

    friend istream& operator>>(istream& in, Array& arr) {
        for (int i = 0; i < arr.size; i++) {
            in >> arr.ptr[i];
        }
        return in;
    }
};

int main() {
    Array<int> arr(5);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    cout << "Array elements: " << arr << endl;

    Array<int> arr2(5);
    arr2 = arr;

    cout << "Copied array: " << arr2 << endl;

    arr2.resize(7);
    cout << "Resized array: " << arr2 << endl;

    return 0;
}
