#include "MyVector.h"

void MyVector::resize(int new_capacity) {
        int* new_data = new int[new_capacity];
        for (int i = 0; i < size; ++i) {
                new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
}

MyVector::MyVector() : data(new int[1]), size(0), capacity(0) {}
MyVector::MyVector(int capacity) : data(new int[capacity]), size(0), capacity(capacity) {}

MyVector::~MyVector() {
                delete[] data;
}

MyVector::MyVector(const MyVector& other) : data(new int[other.capacity]), size(other.size), capacity(other.capacity) {
        memcpy(data, other.data, size * sizeof(int));
}

MyVector& MyVector::operator=(const MyVector& other) {
        if (this != &other) {
                delete[] data;
                capacity = other.capacity;
                size = other.size;
                data = new int[capacity];
                memcpy(data, other.data, size * sizeof(int));
        }
        return *this;
}

        int MyVector::getSize() const{
                return size;
        }

        int MyVector::getCapacity() const{
                return capacity;
        }

        void MyVector::pushBack(const int toAdd) {
                if (capacity == size) {
                        resize(capacity == 0 ? 1 : capacity * 2);
                }
                data[size++] = toAdd;
        }

        void MyVector::popBack() {
                if (size > 0) {
                        --size;
                }
                else {
                        throw std::out_of_range("Vector is empty");
                }
        }

        int MyVector::at(const int index) const{
                if (index >= size) {
                        throw std::out_of_range("Index out of range");
                }
                return data[index];
        }
        void MyVector::print() {
                for (int i = size-1; i >= 0; i--) {
                        printf("%d ", data[i]);
                }
                printf("\n");
        }

        void MyVector::heapify(int n, int i) {
                int largest = i; // Initialize largest as root
                int left = 2 * i + 1; // left = 2*i + 1
                int right = 2 * i + 2; // right = 2*i + 2

                // If left child is larger than root
                if (left < n && data[left] > data[largest])
                        largest = left;

                // If right child is larger than largest so far
                if (right < n && data[right] > data[largest])
                        largest = right;

                // If largest is not root
                if (largest != i) {
                        std::swap(data[i], data[largest]);

                        // Recursively heapify the affected sub-tree
                        heapify(n, largest);
                }
        }

        void MyVector::heapSort() {
                int n = size;

                // Build heap (rearrange array)
                for (int i = n / 2 - 1; i >= 0; i--)
                        heapify(n, i);

                // One by one extract an element from heap
                for (int i = n - 1; i > 0; i--) {
                        // Move current root to end
                        std::swap(data[0], data[i]);

                        // call max heapify on the reduced heap
                        heapify(i, 0);
                }
        }

        void MyVector::sortData() {
                heapSort();
        }
