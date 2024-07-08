#pragma once
#include <iostream>
class MyVector
{
private:
        int* data;
        int size;
        int capacity;
        
        void resize(int new_capacity);
        void heapify(int n, int i);
        void heapSort();


public:
        MyVector();
        MyVector(int capacity);
        ~MyVector();
        MyVector(const MyVector& other);
        MyVector& operator=(const MyVector& other);

        void sortData();
        int getSize() const;
        int getCapacity() const;
        void pushBack(const int toAdd);
        void popBack();
        int at(const int index) const;
        void print();

};
