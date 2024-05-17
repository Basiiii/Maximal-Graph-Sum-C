/**

    @file      graph.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph-structure.h"

/**
 *  @brief  Creates a new graph with the specified number of vertices and hash
 *          table size.
 *  @param  numVertices - The initial number of vertices in the graph.
 *  @param  hashSize    - The size of the hash table used to store vertices.
 *  @retval             - A pointer to the newly created graph.
 *  @retval             - NULL if memory allocation fails.
 */
Graph* CreateGraph(unsigned int numVertices, unsigned int hashSize) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (graph == NULL) {
    return NULL;  // Memory allocation for graph failed
  }

  graph->numVertices = numVertices;
  graph->hashSize = hashSize;
  graph->vertices = (Vertex**)calloc(hashSize, sizeof(Vertex*));
  if (graph->vertices == NULL) {  // Additional check for calloc failure
    free(graph);  // Free previously allocated memory to avoid memory leak
    return NULL;
  }

  return graph;
}

/**
    @brief Displays the graph in a text format to stdout.
    @param graph - The graph to be displayed.
**/
void DisplayGraph(const Graph* graph) {
  if (graph == NULL) {
    printf("Graph is NULL.\n");
    return;
  }

  printf("Graph with %u vertices:\n", graph->numVertices);

  // Iterate over the hash table array to display graph
  for (unsigned int i = 0; i < graph->hashSize; ++i) {
    Vertex* vertex = graph->vertices[i];
    if (vertex == NULL) {
      continue;  // Skip empty slots
    }

    printf("Vertex ID %d -> ", vertex->id);
    if (vertex->edges == NULL) {
      printf("No edges\n");
      continue;  // Skip to next vertex
    }

    // Print edges
    Edge* edge = vertex->edges;
    while (edge != NULL) {
      printf("(%d, %d) ", edge->dest, edge->weight);
      edge = edge->next;
    }
    printf("\n");
  }
}

/**
    @brief Frees a given graph from memory.
    @param graph - The graph to be freed.
**/
void FreeGraph(Graph* graph) {
  if (graph == NULL || graph->vertices == NULL) {
    return;  // Early return if graph or vertices are NULL
  }

  // Free each vertex's edges
  for (unsigned int i = 0; i < graph->hashSize; i++) {
    Vertex* vertex = graph->vertices[i];

    if (vertex == NULL) {
      continue;
    }

    Edge* edge = vertex->edges;
    while (edge != NULL) {
      Edge* nextEdge = edge->next;
      free(edge);       // Free the edge
      edge = nextEdge;  // Move to the next edge
    }

    free(vertex);   // Free the vertex itself
    vertex = NULL;  // Prevent dangling pointer
  }

  // Free the array of vertices
  free(graph->vertices);

  // Free the graph itself
  free(graph);
}
