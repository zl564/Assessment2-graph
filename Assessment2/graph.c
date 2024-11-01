#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

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

// Heuristic function for A* (simple Euclidean distance)
int heuristic(int a, int b) {
    return abs(a - b);
}

// Min-heap helper functions
void minHeapify(MinHeapNode heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && heap[left].dist < heap[smallest].dist)
        smallest = left;
    if (right < n && heap[right].dist < heap[smallest].dist)
        smallest = right;
    if (smallest != i) {
        MinHeapNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, n, smallest);
    }
}

MinHeapNode extractMin(MinHeapNode heap[], int* n) {
    MinHeapNode root = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    minHeapify(heap, *n, 0);
    return root;
}

void decreaseKey(MinHeapNode heap[], int v, int dist, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (heap[i].v == v) {
            heap[i].dist = dist;
            break;
        }
    }
    while (i && heap[i].dist < heap[(i - 1) / 2].dist) {
        MinHeapNode temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// Dijkstra¡¯s Algorithm implementation
void dijkstra(Graph* graph, int start) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES] = { false };
    for (int i = 0; i < MAX_NODES; i++) dist[i] = INF;
    dist[start] = 0;

    MinHeapNode heap[MAX_NODES];
    int size = graph->numNodes;
    for (int i = 0; i < size; i++) heap[i] = (MinHeapNode){ i, dist[i] };

    while (size > 0) {
        MinHeapNode minNode = extractMin(heap, &size);
        int u = minNode.v;
        visited[u] = true;

        Node* adj = graph->adjList[u];
        while (adj) {
            int v = adj->dest;
            if (!visited[v] && dist[u] + adj->weight < dist[v]) {
                dist[v] = dist[u] + adj->weight;
                decreaseKey(heap, v, dist[v], size);
            }
            adj = adj->next;
        }
    }

    printf("Dijkstra distances from start node %d:\n", start);
    for (int i = 0; i < graph->numNodes; i++) printf("Node %d: %d\n", i, dist[i]);
}

// A* Algorithm implementation
void aStar(Graph* graph, int start, int end, int (*heuristic)(int, int)) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES] = { false };
    for (int i = 0; i < MAX_NODES; i++) dist[i] = INF;
    dist[start] = 0;

    MinHeapNode heap[MAX_NODES];
    int size = graph->numNodes;
    for (int i = 0; i < size; i++) heap[i] = (MinHeapNode){ i, dist[i] };

    while (size > 0) {
        MinHeapNode minNode = extractMin(heap, &size);
        int u = minNode.v;
        if (u == end) break;
        visited[u] = true;

        Node* adj = graph->adjList[u];
        while (adj) {
            int v = adj->dest;
            if (!visited[v] && dist[u] + adj->weight < dist[v]) {
                dist[v] = dist[u] + adj->weight;
                decreaseKey(heap, v, dist[v] + heuristic(v, end), size);
            }
            adj = adj->next;
        }
    }

    printf("A* distances from start node %d to end node %d:\n", start, end);
    for (int i = 0; i < graph->numNodes; i++) printf("Node %d: %d\n", i, dist[i]);
}

// Free memory for graph
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numNodes; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph);
}

// Load graph from file
void loadGraphFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int src, dest, weight;
    while (fscanf_s(file, "%d %d %d", &src, &dest, &weight) != EOF) {
        addEdge(graph, src, dest, weight);
    }

    fclose(file);
}

// Generate Watts-Strogatz graph
void generateWattsStrogatzGraph(Graph* graph, int k, double beta, int weight) {
    int numNodes = graph->numNodes;

    // Step 1: Create a ring lattice where each node is connected to `k` neighbors
    for (int i = 0; i < numNodes; i++) {
        for (int j = 1; j <= k / 2; j++) {
            int neighbor = (i + j) % numNodes;
            addEdge(graph, i, neighbor, weight);
            addEdge(graph, neighbor, i, weight);  // For undirected graph symmetry
        }
    }

    // Step 2: Rewire edges with probability `beta`
    for (int i = 0; i < numNodes; i++) {
        for (int j = 1; j <= k / 2; j++) {
            int neighbor = (i + j) % numNodes;
            if (((double)rand() / RAND_MAX) < beta) {
                // Find a new target that is not `i` or any of its current neighbors
                int newNeighbor;
                do {
                    newNeighbor = rand() % numNodes;
                } while (newNeighbor == i || /* Check if `newNeighbor` is already a neighbor of `i` */ ({
                    Node* temp = graph->adjList[i];
                    bool isNeighbor = false;
                    while (temp) {
                        if (temp->dest == newNeighbor) {
                            isNeighbor = true;
                            break;
                        }
                        temp = temp->next;
                    }
                    isNeighbor;
                }));

                // Rewire edge
                // Remove the current edge to `neighbor`
                Node** current = &(graph->adjList[i]);
                while (*current && (*current)->dest != neighbor) {
                    current = &(*current)->next;
                }
                if (*current) {
                    Node* temp = *current;
                    *current = (*current)->next;
                    free(temp);
                }

                // Add new edge
                addEdge(graph, i, newNeighbor, weight);
                addEdge(graph, newNeighbor, i, weight);  // For undirected graph symmetry
            }
        }
    }
}
// Generate Watts-Strogatz graph
void generateWattsStrogatzGraph(Graph* graph, int k, double beta, int weight) {
    int numNodes = graph->numNodes;

    // Step 1: Create a ring lattice where each node is connected to `k` neighbors
    for (int i = 0; i < numNodes; i++) {
        for (int j = 1; j <= k / 2; j++) {
            int neighbor = (i + j) % numNodes;
            addEdge(graph, i, neighbor, weight);
            addEdge(graph, neighbor, i, weight);  // For undirected graph symmetry
        }
    }

    // Step 2: Rewire edges with probability `beta`
    for (int i = 0; i < numNodes; i++) {
        for (int j = 1; j <= k / 2; j++) {
            int neighbor = (i + j) % numNodes;
            if (((double)rand() / RAND_MAX) < beta) {
                // Find a new target that is not `i` or any of its current neighbors
                int newNeighbor;
                do {
                    newNeighbor = rand() % numNodes;
                } while (newNeighbor == i || /* Check if `newNeighbor` is already a neighbor of `i` */ ({
                    Node * temp = graph->adjList[i];
                    bool isNeighbor = false;
                    while (temp) {
                        if (temp->dest == newNeighbor) {
                            isNeighbor = true;
                            break;
                        }
                        temp = temp->next;
                    }
                    isNeighbor;
                    }));

                // Rewire edge
                // Remove the current edge to `neighbor`
                Node** current = &(graph->adjList[i]);
                while (*current && (*current)->dest != neighbor) {
                    current = &(*current)->next;
                }
                if (*current) {
                    Node* temp = *current;
                    *current = (*current)->next;
                    free(temp);
                }

                // Add new edge
                addEdge(graph, i, newNeighbor, weight);
                addEdge(graph, newNeighbor, i, weight);  // For undirected graph symmetry
            }
        }
    }
}
