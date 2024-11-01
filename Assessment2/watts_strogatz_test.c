#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Function to test the generation of a Watts-Strogatz graph
void watts_strogatz_test() {
    int numNodes = 10;  // Number of nodes in the graph
    int k = 4;          // Each node is connected to k nearest neighbors
    double beta = 0.5;  // Rewiring probability
    int weight = 1;     // Weight of each edge

    // Create the graph
    Graph* graph = createGraph(numNodes);
    generateWattsStrogatzGraph(graph, k, beta, weight);

    // Validate the structure of the generated graph
    printf("Testing Watts-Strogatz Graph Generation:\n");

    // Check each node's adjacency list
    for (int i = 0; i < numNodes; i++) {
        Node* current = graph->adjList[i];
        printf("Node %d:", i);
        while (current) {
            printf(" -> (Node: %d, Weight: %d)", current->dest, current->weight);
            current = current->next;
        }
        printf("\n");
    }

    // Check the number of edges for each node
    for (int i = 0; i < numNodes; i++) {
        int edgeCount = 0;
        Node* current = graph->adjList[i];
        while (current) {
            edgeCount++;
            current = current->next;
        }
        printf("Node %d has %d edges (expected: approximately %d)\n", i, edgeCount, 2 * k);
    }

    // Check for valid edge weights
    for (int i = 0; i < numNodes; i++) {
        Node* current = graph->adjList[i];
        while (current) {
            if (current->weight != weight) {
                printf("Error: Node %d has unexpected edge weight %d (expected: %d)\n", i, current->weight, weight);
            }
            current = current->next;
        }
    }

    // Output rewiring probability
    printf("Rewiring Probability: %.2f\n", beta);
    printf("Total nodes: %d\n", numNodes);

    // Clean up
    freeGraph(graph);
}

// Main function to run tests
#ifdef TEST_MODE
int main() {
    // Call the test function for Watts-Strogatz graph
    watts_strogatz_test();

    return 0;
}
#endif
