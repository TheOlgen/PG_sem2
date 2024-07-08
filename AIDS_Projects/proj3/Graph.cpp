#include "Graph.h"
#include <iostream>

// Resize the adjacency list
void Graph::resize(int new_capacity) {
    MyVector* new_list = new MyVector[new_capacity];
    for (int i = 0; i < vertices; ++i) {
        new_list[i] = list[i];
    }
    delete[] list;
    list = new_list;
    capacity = new_capacity;
}

Graph::Graph() : list(nullptr), vertices(0), capacity(0) {}

Graph::Graph(int vertices) : vertices(0), capacity(vertices) {
    list = new MyVector[vertices];
}

Graph::~Graph() {
    delete[] list;
}
Graph::Graph(const Graph& other) : list(new MyVector[other.capacity]), vertices(other.vertices), capacity(other.capacity) {
    for (int i = 0; i < vertices; ++i) {
        list[i] = other.list[i];
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        delete[] list;
        capacity = other.capacity;
        vertices = other.vertices;
        list = new MyVector[capacity];
        for (int i = 0; i < vertices; ++i) {
            list[i] = other.list[i];
        }
    }
    return *this;
}

int Graph::getCapacity() const{
    return capacity;
}

int Graph::getVertices() const {
    return vertices;
}

void Graph::pushBack(MyVector& to_add) {
    if (vertices == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    list[vertices] = to_add;
    ++vertices;
}

void Graph::popBack() {
    if (vertices > 0) {
        --vertices;
    }
    else {
        throw std::out_of_range("Graph is empty");
    }
}

void Graph::print() const {
    for (int i = 0; i < vertices; ++i) {
        std::cout << i << ": ";
        list[i].print();
        std::cout << std::endl;
    }
}

MyVector& Graph::at(const int index) {
    if (index >= vertices) {
        throw std::out_of_range("Index out of range");
    }
    return list[index] ;
}

unsigned long long Graph::countEdges() const {
    unsigned long long edges = 0;
    for (int i = 0; i < vertices; ++i) {
        edges +=(unsigned long long) list[i].getSize();
    }
    return edges / 2; 
}

/*
// Add an edge between vertices u and v
void Graph::addEdge(int u, int v) {
    if (u < vertices && v < vertices) {
        list[u].pushBack(v);
        // Uncomment the next line if the graph is undirected
        // list[v].pushBack(u);
    }
}*/
