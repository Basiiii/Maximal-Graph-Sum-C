/**

    @file      edges.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      16.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include "edges.h"

#include <stdbool.h>
#include <stdlib.h>

#include "graph.h"
#include "vertices.h"

/**
  @brief  Creates a new edge with the specified destination and weight.
  @param  dest   - The destination of this edge.
  @param  weight - The weight of this edge.
  @retval        - A pointer to the newly created edge.
  @retval        - NULL if memory allocation fails.
**/
Edge* CreateEdge(unsigned int dest, unsigned int weight) {
  Edge* newEdge = (Edge*)malloc(sizeof(Edge));
  if (newEdge == NULL) {
    return NULL;  // Memory allocation for edge failed
  }

  newEdge->dest = dest;
  newEdge->weight = weight;
  newEdge->next = NULL;

  return newEdge;
}

/**
  @brief  Adds an edge to a vertex.
  @param  vertex - The vertex to which we add the edge.
  @param  edge   - The edge to be added.
  @retval        - True in the case of success.
  @retval        - False if vertex or edge are NULL.
**/
bool AddEdgeToVertex(Vertex* vertex, Edge* edge) {
  if (vertex == NULL || edge == NULL) {
    return false;
  }

  edge->next = vertex->edges;
  vertex->edges = edge;

  return true;
}

/**
    @brief  Creates an edge and adds it to a vertex.
    @param  vertex - The vertex which will have the new edge.
    @param  dest   - The destination of the edge.
    @param  weight - The weight of the edge.
    @retval        - True if the edge was succesfully created and added.
    @retval        - False if edge already exists or in the event of an error.
**/
bool CreateAddEdge(Vertex* vertex, unsigned int dest, unsigned int weight) {
  if (EdgeExists(vertex, dest)) {
    return false;
  }

  Edge* edge = CreateEdge(dest, weight);
  if (edge == NULL) {
    return false;
  }

  bool res = AddEdgeToVertex(vertex, edge);
  if (res == false) {
    free(edge);
    return false;
  }

  return true;
}

/**
  @brief  Checks if an edge exists.
  @param  vertex - The vertex where the edge starts.
  @param  dest   - The destination of the edge.
  @retval        - True if the edge exists.
  @retval        - False if the edge does not exist.
**/
bool EdgeExists(Vertex* vertex, unsigned int dest) {
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

/**
  @brief  Checks if an edge exists between two given vertex ID's.
  @param  graph - The graph which contains the vertices and edges.
  @param  src   - The identifier of the source vertex.
  @param  dest  - The identifier of the destination vertex.
  @retval       - True if the edge exists.
  @retval       - False if the edge does not exist.
**/
bool EdgeExistsBetweenVertices(const Graph* graph, unsigned int src,
  unsigned int dest) {
  Vertex* sourceVertex = FindVertex(graph, src);
  if (sourceVertex == NULL) {
    return false;
  }

  return EdgeExists(sourceVertex, dest);
}

/**
  @brief Removes a specific edge from a vertex.
  @param vertex - The vertex which contains the edge.
  @param dest   - The destination of the edge.
  @retval       - SUCCESS_REMOVING_EDGE if the edge was removed.
  @retval       - INVALID_VERTEX if the vertex is invalid.
  @retval       - EDGE_DOES_NOT_EXIST if the edge does not exist.
  @retval       - UNDEFINED_ERROR if edge was not found.
**/
int RemoveEdge(Vertex* vertex, unsigned int dest) {
  if (vertex == NULL || vertex->edges == NULL) {
    return INVALID_VERTEX;
  }

  if (!EdgeExists(vertex, dest)) {
    return EDGE_DOES_NOT_EXIST;
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
      }
      else {
        // Edge is somewhere in the middle or at the end of the list
        prevEdge->next = currentEdge->next;
      }
      free(currentEdge);
      return SUCCESS_REMOVING_EDGE;
    }
    prevEdge = currentEdge;
    currentEdge = currentEdge->next;
  }

  return UNDEFINED_ERROR;
}

/**
  @brief Removes all outgoing edges from a vertex.
  @param vertex - The vertex from which to remove all outgoing edges.
  @retval       - SUCCESS_REMOVING_OUTGOING_EDGES if all edges were removed.
  @retval       - VERTEX_EDGES_NULL if the vertex or its edges are NULL.
  @retval       - ERROR_REMOVING_EDGE if there was an error removing an edge.
**/
int RemoveOutgoingEdges(Vertex* vertex) {
  if (vertex == NULL || vertex->edges == NULL) {
    return VERTEX_EDGES_NULL;
  }

  // Initialize a temporary pointer to hold the next edge
  Edge* currentEdge = vertex->edges;
  Edge* tempEdge = NULL;

  // Iterate over the outgoing edges
  while (currentEdge != NULL) {
    // Store the next edge in tempEdge before freeing currentEdge
    tempEdge = currentEdge->next;

    // Free the current edge
    free(currentEdge);

    // Move to the next edge
    currentEdge = tempEdge;
  }

  // Set the vertex's edges to NULL as all edges are removed
  vertex->edges = NULL;

  return SUCCESS_REMOVING_OUTGOING_EDGES;
}

/**
  @brief Removes edges pointing to a specific vertex from a vertex's edge
         list.
  @param vertex         - The vertex from which to remove edges.
  @param targetVertexId - The ID of the vertex to which the edges point.
  @retval               - SUCCESS_REMOVING_EDGES if all edges were removed.
  @retval               - ERROR_REMOVING_EDGE if there was an error removing
                          an edge.
**/
int RemoveEdgesPointingTo(Vertex* vertex, unsigned int targetVertexId) {
  Edge* currentEdge = vertex->edges;
  Edge* prevEdge = NULL;

  while (currentEdge != NULL) {
    if (currentEdge->dest == targetVertexId) {
      // Save the next edge before removing the current one
      Edge* nextEdge = currentEdge->next;

      // Remove the edge pointing to the target vertex
      if (prevEdge == NULL) {
        vertex->edges = nextEdge;
      }
      else {
        prevEdge->next = nextEdge;
      }
      free(currentEdge);

      currentEdge = nextEdge;
    }
    else {
      prevEdge = currentEdge;
      currentEdge = currentEdge->next;
    }
  }

  return SUCCESS_REMOVING_EDGES;
}

/**
  @brief Removes all incoming edges to a specified vertex in the graph.
  @param graph    - The graph from which to remove incoming edges.
  @param vertexId - The ID of the vertex for which to remove incoming edges.
  @retval         - SUCCESS_REMOVING_INCOMING_EDGES if all edges were removed.
  @retval         - INVALID_GRAPH if the graph is NULL.
  @retval         - ERROR_REMOVING_EDGE if there was an error removing an edge.
**/
int RemoveIncomingEdges(const Graph* graph, unsigned int vertexId) {
  if (graph == NULL) {
    return INVALID_GRAPH;
  }

  // Iterate through all slots in the hash table
  for (unsigned int i = 0; i < graph->hashSize; i++) {
    Vertex* vertex = graph->vertices[i];
    if (vertex != NULL) {
      int result = RemoveEdgesPointingTo(vertex, vertexId);
      if (result != SUCCESS_REMOVING_EDGES) {
        return ERROR_REMOVING_EDGE;
      }
    }
  }

  return SUCCESS_REMOVING_INCOMING_EDGES;
}
