#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

int main() {
    // Create a graph and load data from file
    Graph* graph = createGraph(MAX_NODES);

    // Sample edges; you can also load this from "input.txt" for larger datasets
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 3);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 5);

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

    free(graph);
    return 0;
}
