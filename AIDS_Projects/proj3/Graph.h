#pragma once
#include "MyVector.h"
class Graph
{
private:
        MyVector* list;
        int vertices;
        int capacity;

        void resize(int new_size);

public:
        Graph();
        Graph(int verticles);
        ~Graph();
        Graph(const Graph& other);
        Graph& operator=(const Graph& other);

        unsigned long long countEdges() const;
        int getCapacity() const;
        int getVertices() const;
        void pushBack(MyVector& to_add);
        void popBack();
        void print() const;
        MyVector& at(int index);
};
