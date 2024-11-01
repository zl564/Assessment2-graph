#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Function to simulate various operations on the graph
void performGraphOperations(Graph* graph) {
    printf("Performing graph operations...\n");

    // Adding some edges 
    for (int i = 0; i < graph->numNodes; i++) {
        for (int j = i + 1; j < graph->numNodes && j < i + 5; j++) {
            addEdge(graph, i, j, rand() % 10 + 1); // Random weight between 1 and 10
        }
    }

    // Printing the graph for verification
    for (int i = 0; i < graph->numNodes; i++) {
        printf("Node %d: ", i);
        Node* temp = graph->adjList[i];
        while (temp) {
            printf(" -> (%d, %d)", temp->dest, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void runMemoryTests() {
    int numNodes = 100;  // Size of the graph
    Graph* graph = createGraph(numNodes);

    performGraphOperations(graph);

    // Free the allocated memory
    freeGraph(graph);
    printf("Memory test completed. \n");
}

// Main function 
#ifdef TEST_MODE
int main() {
    runMemoryTests();
    return 0;
}
#endif