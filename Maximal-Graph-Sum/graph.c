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

/**
 *  @brief
 *  @param  numVertices -
 *  @param  hashSize    -
 *  @retval             -
 */
Graph* CreateGraph(int numVertices, int hashSize) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (graph != NULL) {
    graph->numVertices = numVertices;
    graph->hashSize = hashSize;
    graph->vertices = (Vertex**)calloc(hashSize, sizeof(Vertex*));
  }
  return graph;
}

Edge* CreateEdge(int dest, int weight) {
  Edge* newEdge = (Edge*)malloc(sizeof(Edge));
  if (newEdge != NULL) {
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = NULL;
  }
  return newEdge;
}

void AddEdge(Vertex* vertex, int dest, int weight) {
  Edge* newEdge = CreateEdge(dest, weight);
  if (newEdge == NULL) {
    exit(EXIT_FAILURE);
  }

  // Add the new edge to the beginning of the list
  newEdge->next = vertex->edges;
  vertex->edges = newEdge;
}

bool EdgeExists(Vertex* vertex, int dest) {
  Edge* currentEdge = vertex->edges;
  while (currentEdge != NULL) {
    if (currentEdge->dest == dest) {
      // Edge already exists
      return true;
    }
    currentEdge = currentEdge->next;
  }
  // Edge does not exist
  return false;
}

void DisplayGraph(const Graph* graph) {
  if (graph == NULL) {
    printf("Graph is NULL\n");
    return;
  }

  printf("Graph with %d vertices:\n", graph->numVertices);

  for (int i = 0; i < graph->hashSize; ++i) {
    Vertex* vertex = graph->vertices[i];
    if (vertex == NULL) {
      continue;  // Skip empty slots
    }

    printf("Vertex index %d -> ", vertex->id);
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

// Function to check if an edge exists between two vertices
bool EdgeExistsBetweenVertices(const Graph* graph, int src, int dest) {
  if (!VertexExists(graph, src) || !VertexExists(graph, dest)) {
    return false;
  }

  Vertex* sourceVertex = graph->vertices[Hash(src, graph->hashSize)];
  return EdgeExists(sourceVertex, dest);
}

// Function to remove an edge from a vertex
void RemoveEdge(Vertex* vertex, int dest) {
  if (vertex == NULL || vertex->edges == NULL) {
    return;
  }

  if (!EdgeExists(vertex, dest)) {
    // Edge doesn't exist, nothing to remove
    return;
  }

  Edge* prevEdge = NULL;
  Edge* currentEdge = vertex->edges;

  // Traverse the list of edges to find the edge to remove
  while (currentEdge != NULL) {
    if (currentEdge->dest == dest) {
      // Remove the edge from the list
      if (prevEdge == NULL) {
        // Edge is the first one in the list
        vertex->edges = currentEdge->next;
      } else {
        // Edge is somewhere in the middle or at the end of the list
        prevEdge->next = currentEdge->next;
      }
      free(currentEdge);
      return;
    }
    prevEdge = currentEdge;
    currentEdge = currentEdge->next;
  }
}

void DeleteGraph(Graph* graph) {
  if (graph == NULL || graph->vertices == NULL) {
    return;  // Early return if graph or vertices are NULL
  }

  // Free each vertex's edges
  for (int i = 0; i < graph->hashSize; i++) {
    Vertex* vertex = graph->vertices[i];
    while (vertex != NULL) {
      Edge* edge = vertex->edges;
      while (edge != NULL) {
        Edge* nextEdge = edge->next;
        free(edge);       // Free the edge
        edge = nextEdge;  // Move to the next edge
      }
      vertex->edges = NULL;  // Ensure edges pointer is NULL after deletion
      free(vertex);          // Free the vertex itself
      vertex = NULL;         // Prevent dangling pointer
    }
  }

  // Free the array of vertices
  free(graph->vertices);

  // Free the graph itself
  free(graph);
}
