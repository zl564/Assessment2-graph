#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct MinHeapNode {
    int v;
    int dist;
} MinHeapNode;

// Create a graph with given nodes
Graph* createGraph(int nodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = nodes;
    for (int i = 0; i < nodes; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Add edge to graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// Min-heap helper functions
void minHeapify(MinHeapNode heap[], int n, int i) { /* Implementation omitted for brevity */ }

// Dijkstra¡¯s Algorithm implementation
void dijkstra(Graph* graph, int start) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES] = { false };

    for (int i = 0; i < MAX_NODES; i++) dist[i] = INF;
    dist[start] = 0;

    MinHeapNode heap[MAX_NODES];
    for (int i = 0; i < graph->numNodes; i++) heap[i] = (MinHeapNode){ i, dist[i] };

    for (int i = 0; i < graph->numNodes; i++) {
        // Extract minimum distance node (pseudo-heap operation for simplicity)
        int u = -1;
        for (int j = 0; j < graph->numNodes; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) u = j;
        }

        visited[u] = true;
        Node* adj = graph->adjList[u];
        while (adj) {
            int v = adj->dest;
            if (!visited[v] && dist[u] + adj->weight < dist[v]) {
                dist[v] = dist[u] + adj->weight;
            }
            adj = adj->next;
        }
    }

    printf("Dijkstra distances from start node %d:\n", start);
    for (int i = 0; i < graph->numNodes; i++) printf("Node %d: %d\n", i, dist[i]);
}

// Heuristic function for A* (simple Euclidean distance)
int heuristic(int a, int b) {
    return abs(a - b); // Placeholder; normally use coordinates for Euclidean distance
}

// A* Algorithm implementation
void aStar(Graph* graph, int start, int end, int (*heuristic)(int, int)) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES] = { false };

    for (int i = 0; i < MAX_NODES; i++) dist[i] = INF;
    dist[start] = 0;

    MinHeapNode heap[MAX_NODES];
    for (int i = 0; i < graph->numNodes; i++) heap[i] = (MinHeapNode){ i, dist[i] };

    for (int i = 0; i < graph->numNodes; i++) {
        int u = -1;
        for (int j = 0; j < graph->numNodes; j++) {
            if (!visited[j] && (u == -1 || dist[j] + heuristic(j, end) < dist[u] + heuristic(u, end))) u = j;
        }

        if (u == end) break;
        visited[u] = true;

        Node* adj = graph->adjList[u];
        while (adj) {
            int v = adj->dest;
            if (!visited[v] && dist[u] + adj->weight < dist[v]) {
                dist[v] = dist[u] + adj->weight;
            }
            adj = adj->next;
        }
    }

    printf("A* distance from node %d to node %d: %d\n", start, end, dist[end]);
}