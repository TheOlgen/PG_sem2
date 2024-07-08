// AIDSproj3.cpp : Ten plik zawiera funkcjÄ âmainâŁ. W nim rozpoczyna siÄ i koÅczy wykonywanie programu.
//

#include <iostream>
#include "MyVector.h"
#include "Graph.h"

#define NO_SIDE 0
#define RIGHT 1
#define LEFT 2

#define NO_COLOR 0
#define FILL 1
#define CLEAR 0

using namespace std;

void initializeGraph(Graph &graf) 
{
    MyVector degreeSequence(graf.getCapacity());
    //graf.pushBack(degreeSequence);
    int degree = 0, num = 0;
    for (int j = 0; j < graf.getCapacity(); j++) 
    {
        scanf_s("%d", &degree);
        degreeSequence.pushBack(degree);
        MyVector line = MyVector(degree);
        for (int k = 0; k < degree; k++) 
        {
            scanf_s("%d", &num);
            line.pushBack(num);    
        }
        graf.pushBack(line);  
    }
    degreeSequence.sortData();
    degreeSequence.print();
}

void DFS(Graph& graf, int v, bool visited[]) {
    visited[v] = true;
    MyVector& neighbors = graf.at(v);
    for (int i = 0; i < neighbors.getSize(); i++) {
        int u = neighbors.at(i) - 1;
        if (!visited[u]) {
            visited[u] = true;
            DFS(graf, u, visited);
        }
    }
}

void numberOfCompoments(Graph& graf) 
{
    bool* visited = new bool[graf.getVertices()]();
    int count = 0;
    for (int v = 0; v < graf.getVertices(); v++) {
        if (!visited[v]) {
            DFS(graf, v, visited);
            count++;
        }
    }
    delete[] visited;
    printf("%d\n", count);
}

void complementEdges(Graph& graf) {
    unsigned long long edges = graf.countEdges();
    unsigned long long maxEdges = (unsigned long long)graf.getVertices() * ((unsigned long long)graf.getVertices() - 1) / 2;
    unsigned long long complementEdges = maxEdges - edges;
    printf("%lld \n", complementEdges);
}

bool matchSides(Graph& graf, int index, int sides[]) 
{
    MyVector& neighbors = graf.at(index);
    int side, otherside, current;
    side = sides[index];
    otherside = (side == RIGHT ? LEFT : RIGHT);
    for (int i = 0; i < neighbors.getSize(); i++) {
        current = neighbors.at(i)-1;
        if (sides[current] == side) {
            return false;
        }
        else if (sides[current] == NO_SIDE) {
            sides[current] = otherside;
        if (!matchSides(graf, current, sides))
            return false;
        }
    }
    return true;
}

void bipartenes(Graph& graf) 
{
    int* sides = new int[graf.getVertices()]();
    for (int i = 0; i < graf.getVertices(); i++) {
        sides[i] = NO_SIDE;
    }
    for (int i = 0; i < graf.getVertices(); i++) {
        if (sides[i] == NO_SIDE) {
            sides[i] = RIGHT;
            if (!matchSides(graf, i, sides)) {
                printf("F\n");
                return;
            }
        }
    }
    printf("T\n");
}

void newUsedColors(Graph& graf, int index, int coloredGraph[], bool usedColors[], bool mode)
{
    int current;
    for (int i = 0; i < graf.at(index).getSize(); i++) {
        current = graf.at(index).at(i) - 1;
        if (coloredGraph[current] != NO_COLOR) {
            usedColors[coloredGraph[current]] = mode; //mode mozna wywoÅac jako FILL samymi jedynkami albo CREAR samymi zerami
        }
    }
}

int chooseColor(bool usedColors[], int size) 
{
    for (int color = 1; color <= size; color++) {
        if (!usedColors[color]) {
            return color;
        }
    }
    return size;
}

void colorGreedy(Graph& graf)
{
    bool* usedColors = new bool[graf.getVertices() + 1]();
    int* coloredGraph = new int[graf.getVertices()];
    for (int i = 0; i < graf.getVertices(); i++) {
        coloredGraph[i] = NO_COLOR;
    }

    for (int i = 0; i < graf.getVertices(); i++) {
        newUsedColors(graf, i, coloredGraph, usedColors, FILL);
        coloredGraph[i] = chooseColor(usedColors, i+1);
        newUsedColors(graf, i, coloredGraph, usedColors, CLEAR);
    }

    for (int i = 0; i < graf.getVertices(); i++) {
        printf("%d ", coloredGraph[i]);
    }
    printf("\n");

    delete[] usedColors;
    delete[] coloredGraph;
}


void printParameters(Graph& graf) 
{
    numberOfCompoments(graf); 
    bipartenes(graf);
    for (int i = 0; i < 2; i++) {
        printf("?\n");
    }
    colorGreedy(graf);
    for (int i = 0; i < 3; i++) {
        printf("?\n");
    }
    complementEdges(graf);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int numOfGraphs, size = 0;
    std::cin >> numOfGraphs;
    for (int i = 0; i < numOfGraphs; i++) {
        scanf_s("%d", &size);
        Graph graf = Graph(size);
        initializeGraph(graf);
        printParameters(graf);
    } 
}
