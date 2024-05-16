/**
 *
 *  @file      vertices.c
 *  @brief
 *  @details   ~
 *  @author    Enrique Rodrigues
 *  @date      15.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 *
 */
#include "vertices.h"

#include "graph.h"

/**
 *  @brief
 *  @param  vertexID -
 *  @param  hashSize -
 *  @retval          -
 */
// int Hash(int vertexID, int hashSize) { return vertexID % hashSize; }

// Ther are other implemetnations on the text file, check which one si fastest
// and which is easiest to implement
int Hash(int vertexID, int hashSize) {
  // Test this implementation to see if it gives you different index vlaues
  unsigned long hash = 0;
  int remainder = 1;

  while (remainder > 0) {
    remainder = vertexID % hashSize;
    hash = (hash << 5) + hash + remainder;
    vertexID /= hashSize;
  }

  return hash;
}

/**
 *  @brief  Checks if a vertex exists or not.
 *  @param  graph       - The graph where the vertex should be.
 *  @param  vertexID    - The index where the vertex should be.
 *  @retval             - True if vertex exists or False if not.
 */
bool VertexExists(const Graph* graph, int vertexID) {
  int index = Hash(vertexID, graph->hashSize);
  return graph->vertices[index] != NULL;
}

/**
 *  @brief
 *  @param  vertexIndex -
 *  @retval             -
 */
Vertex* CreateVertex(int vertexID) {
  Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
  if (newVertex == NULL) {
    return NULL;
  }

  newVertex->id = vertexID;
  newVertex->edges = NULL;

  return newVertex;
}

/**
 *  @brief
 *  @param graph       -
 *  @param vertexIndex -
 */
void AddVertex(Graph* graph, int vertexID, Vertex* vertex) {
  int index = Hash(vertexID, graph->hashSize);
  graph->vertices[index] = vertex;
}

/**
 *  @brief
 *  @param graph       -
 *  @param vertexIndex -
 */
int CreateAddVertex(Graph* graph, int vertexIndex) {
  Vertex* vertex = NULL;

  if (VertexExists(graph, vertexIndex)) {
    return VERTEX_ALREADY_EXISTS;
  }

  vertex = CreateVertex(vertexIndex);
  if (vertex == NULL) {
    return FAILURE_CREATE_VERTEX;
  }

  AddVertex(graph, vertexIndex, vertex);
  return EXIT_SUCCESS;
}

/**
 *  @brief
 *  @param  graph       -
 *  @param  vertexIndex -
 *  @retval             -
 */
Vertex* FindVertex(const Graph* graph, int vertexID) {
  if (!VertexExists(graph, vertexID)) {
    return NULL;
  }

  int index = Hash(vertexID, graph->hashSize);
  return graph->vertices[index];
}

/**
 *  @brief
 *  @param graph       -
 *  @param vertexIndex -
 */
void RemoveVertex(Graph* graph, int vertexIndex) {
  if (graph == NULL || !VertexExists(graph, vertexIndex)) {
    return;
  }

  Vertex* vertexToRemove = FindVertex(graph, vertexIndex);
  int index = Hash(vertexIndex, graph->hashSize);

  // Remove all edges connected to the vertex
  Edge* edge = vertexToRemove->edges;
  while (edge != NULL) {
    Edge* nextEdge = edge->next;  // Store the next edge pointer
    RemoveEdge(FindVertex(graph, vertexIndex), edge->dest);
    edge = nextEdge;  // Move to the next edge
  }

  // Free the memory allocated for the edges of the vertex
  edge = vertexToRemove->edges;
  Edge* nextEdge;
  while (edge != NULL) {
    nextEdge = edge->next;
    free(edge);
    edge = nextEdge;
  }

  // Update indices of remaining vertices in the graph
  for (int i = 0; i < graph->hashSize; ++i) {
    Vertex* currentVertex = graph->vertices[i];
    if (currentVertex != NULL && currentVertex->id > vertexIndex) {
      currentVertex->id--;  // Decrement the index of vertices greater
                            // than the removed one
    }
  }

  // Free the memory allocated for the vertex itself
  free(vertexToRemove);

  // Set the pointer to NULL in the vertices array
  graph->vertices[index] = NULL;
}
