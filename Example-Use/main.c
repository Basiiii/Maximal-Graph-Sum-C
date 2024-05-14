/**

    @file      main.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include <stdio.h>

#include "graph.h"

int main() {
  // Create a graph with 5 vertices
  int numVertices = 5;
  Graph* graph = CreateGraph(numVertices, DEFAULT_HASH_SIZE);
  if (graph == NULL) {
    fprintf(stderr, "Failed to create graph\n");
    return EXIT_FAILURE;
  }

  // Add vertices to the graph
  for (int i = 0; i < numVertices; i++) {
    AddVertex(graph, i);
  }

  DisplayGraph(graph);

  printf("\nAdding edges:\n");
  AddEdge(graph->vertices[0], 1,
          10);  // Edge from vertex 0 to vertex 1 with weight 10
  AddEdge(graph->vertices[0], 2,
          20);  // Edge from vertex 0 to vertex 2 with weight 20
  AddEdge(graph->vertices[1], 3,
          30);  // Edge from vertex 1 to vertex 3 with weight 30
  AddEdge(graph->vertices[2], 3,
          40);  // Edge from vertex 2 to vertex 3 with weight 40
  AddEdge(graph->vertices[3], 4,
          50);  // Edge from vertex 3 to vertex 4 with weight 50
  DisplayGraph(graph);
  printf("\n\n");

  printf("Removing edges\n");

  RemoveEdge(FindVertex(graph, 0), 1);
  RemoveEdge(FindVertex(graph, 0), 2);
  DisplayGraph(graph);
  printf("\n\n");

  printf("Removing vertex\n");

  RemoveVertex(graph, 2);
  graph->numVertices = 4;
  DisplayGraph(graph);
  printf("\n\n");

  DeleteGraph(graph);

  return 0;
}
