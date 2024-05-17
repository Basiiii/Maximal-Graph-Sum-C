/**

    @file      graph.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include "graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 *  @brief  Creates a new graph with the specified number of vertices and hash
 *          table size.
 *  @param  hashSize    - The size of the hash table used to store vertices.
 *  @retval             - A pointer to the newly created graph.
 *  @retval             - NULL if memory allocation fails.
 */
Graph* CreateGraph(unsigned int hashSize) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (graph == NULL) {
    return NULL;  // Memory allocation for graph failed
  }

  graph->numVertices = 0;
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

    while (vertex != NULL) {  // Traverse the linked list of vertices
      printf("Vertex ID %d -> ", vertex->id);

      if (vertex->edges == NULL) {
        printf("No edges\n");
      }
      else {
        PrintEdges(vertex->edges);
      }

      vertex = vertex->next;  // Move to the next vertex in the linked list
    }
  }
}

/**
    @brief Prints all edges within an edges linked list.
    @param edge - The first edge.
**/
void PrintEdges(const Edge* edge) {
  while (edge != NULL) {
    printf("(%d, %d) ", edge->dest, edge->weight);
    edge = edge->next;
  }
  printf("\n");
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
    while (vertex != NULL) {
      Vertex* nextVertex = vertex->next;

      // Free all edges of the current vertex
      Edge* edge = vertex->edges;
      while (edge != NULL) {
        Edge* nextEdge = edge->next;
        free(edge);       // Free the edge
        edge = nextEdge;  // Move to the next edge
      }

      free(vertex);         // Free the vertex itself
      vertex = nextVertex;  // Move to the next vertex in the linked list
    }
  }

  // Free the array of vertices
  free(graph->vertices);

  // Free the graph itself
  free(graph);
}
