#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

// Function prototypes
void loadGraphFromFile(Graph* graph, const char* filename);

int main() {
    // List of available input files
    const char* inputFiles[] = {
        "input1.txt",
        "input2.txt",
        "input3.txt",
        "input4.txt",
        "input5.txt"
    };
    int fileCount = sizeof(inputFiles) / sizeof(inputFiles[0]);

    // Display the options to the user
    printf("Select an input file:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%d: %s\n", i + 1, inputFiles[i]);
    }

    // Get user choice
    int choice;
    printf("Enter your choice (1-%d): ", fileCount);
    scanf_s("%d", &choice);

    // Validate the choice
    if (choice < 1 || choice > fileCount) {
        fprintf(stderr, "Invalid choice. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Create a graph
    Graph* graph = createGraph(MAX_NODES);

    // Load edges from the selected input file
    loadGraphFromFile(graph, inputFiles[choice - 1]);

    // Define start and end nodes for pathfinding
    int start = 0;
    int end = 4;

    // Measure execution time for Dijkstra's algorithm
    clock_t begin = clock();
    dijkstra(graph, start);
    clock_t end_dijkstra = clock();
    printf("Dijkstra's Time: %lf seconds\n", (double)(end_dijkstra - begin) / CLOCKS_PER_SEC);

    // Measure execution time for A* algorithm
    begin = clock();
    aStar(graph, start, end, heuristic);
    clock_t end_a_star = clock();
    printf("A* Time: %lf seconds\n", (double)(end_a_star - begin) / CLOCKS_PER_SEC);

    // Free the allocated graph memory
    freeGraph(graph);

    return 0;
}
