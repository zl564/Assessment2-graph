#ifndef GRAPH_H
#define GRAPH_H

#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 100
#define INF INT_MAX

// Node structure for adjacency list
typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    Node* adjList[MAX_NODES];
    int numNodes;
} Graph;

// Min-Heap Node structure
typedef struct MinHeapNode {
    int v;
    int dist;
} MinHeapNode;

// Function prototypes
Graph* createGraph(int nodes);
void addEdge(Graph* graph, int src, int dest, int weight);
void dijkstra(Graph* graph, int start);
void aStar(Graph* graph, int start, int end, int (*heuristic)(int, int));
int heuristic(int a, int b);

#endif // GRAPH_H
