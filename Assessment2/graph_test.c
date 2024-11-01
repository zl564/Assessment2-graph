#include <stdio.h>
#include <stdlib.h>
#include "graph.h"  

//Test function to create a graph and verify its initial structure
void test_createGraph() {
    int nodes = 5;
    Graph* graph = createGraph(nodes);

    if (graph->numNodes == nodes) {
        printf("Graph creation test passed: Correct number of nodes.\n");
    }
    else {
        printf("Graph creation test failed: Incorrect number of nodes.\n");
    }

    for (int i = 0; i < nodes; i++) {
        if (graph->adjList[i] == NULL) {
            printf("Node %d adjacency list initialized correctly.\n", i);
        }
        else {
            printf("Node %d adjacency list initialization failed.\n", i);
        }
    }

    freeGraph(graph);  // Clean up memory
}

// Test function for adding edges to the graph and checking adjacency lists
void test_addEdge() {
    Graph* graph = createGraph(5);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 15);
    addEdge(graph, 1, 3, 12);
    addEdge(graph, 2, 4, 10);

    // Verify adjacency lists
    if (graph->adjList[0] && graph->adjList[0]->dest == 2 && graph->adjList[0]->weight == 15) {
        printf("Edge (0 -> 2) added successfully.\n");
    }
    if (graph->adjList[1] && graph->adjList[1]->dest == 3 && graph->adjList[1]->weight == 12) {
        printf("Edge (1 -> 3) added successfully.\n");
    }

    freeGraph(graph);  // Clean up memory
}

// Test function for Dijkstra¡¯s algorithm on a sample graph
void test_dijkstra() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 15);
    addEdge(graph, 1, 3, 12);
    addEdge(graph, 2, 4, 10);
    addEdge(graph, 3, 4, 2);

    printf("Running Dijkstra's algorithm from node 0:\n");
    dijkstra(graph, 0);

    freeGraph(graph);  // Clean up memory
}

// Test function for A* algorithm on a sample graph
void test_aStar() {
    Graph* graph = createGraph(5);
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 15);
    addEdge(graph, 1, 3, 12);
    addEdge(graph, 2, 4, 10);
    addEdge(graph, 3, 4, 2);

    printf("Running A* algorithm from node 0 to node 4:\n");
    aStar(graph, 0, 4, heuristic);

    freeGraph(graph);  // Clean up memory
}

// Test function for generating a Watts-Strogatz graph
void test_generateWattsStrogatzGraph() {
    int nodes = 10;
    int k = 4;
    double beta = 0.3;
    int weight = 5;

    Graph* graph = createGraph(nodes);
    generateWattsStrogatzGraph(graph, k, beta, weight);

    printf("Watts-Strogatz graph generated with %d nodes, %d neighbors, beta = %.1f, and edge weight = %d:\n", nodes, k, beta, weight);
    for (int i = 0; i < nodes; i++) {
        printf("Node %d: ", i);
        Node* adj = graph->adjList[i];
        while (adj) {
            printf("(%d, %d) ", adj->dest, adj->weight);
            adj = adj->next;
        }
        printf("\n");
    }

    freeGraph(graph);  // Clean up memory
}

// Main function 
#ifdef TEST_MODE
int main() {
    printf("Running graph tests...\n");

    printf("\nTest 1: Graph Creation\n");
    test_createGraph();

    printf("\nTest 2: Adding Edges\n");
    test_addEdge();

    printf("\nTest 3: Dijkstra's Algorithm\n");
    test_dijkstra();

    printf("\nTest 4: A* Algorithm\n");
    test_aStar();

    printf("\nTest 5: Watts-Strogatz Graph Generation\n");
    test_generateWattsStrogatzGraph();

    printf("\nAll tests completed.\n");
    return 0;
}
#endif