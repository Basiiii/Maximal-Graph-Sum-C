/**

    @file      edges.h
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      16.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#ifndef EDGES_H
#define EDGES_H

#include <stdbool.h>

#include "graph.h"

/**
  @brief  Creates a new edge with the specified destination and weight.
  @param  dest   - The destination of this edge.
  @param  weight - The weight of this edge.
  @retval        - A pointer to the newly created edge.
  @retval        - NULL if memory allocation fails.
**/
Edge* CreateEdge(unsigned int dest, unsigned int weight);

/**
  @brief  Adds an edge to a vertex.
  @param  vertex - The vertex to which we add the edge.
  @param  edge   - The edge to be added.
  @retval        - True in the case of success.
  @retval        - False if vertex or edge are NULL.
**/
bool AddEdgeToVertex(Vertex* vertex, Edge* edge);

/**
    @brief  Creates an edge and adds it to a vertex.
    @param  vertex - The vertex which will have the new edge.
    @param  dest   - The destination of the edge.
    @param  weight - The weight of the edge.
    @retval        - True if the edge was succesfully created and added.
    @retval        - False in the event of an error.
**/
bool CreateAddEdge(const Vertex* vertex, unsigned int dest,
  unsigned int weight);

/**
  @brief  Checks if an edge exists.
  @param  vertex - The vertex where the edge starts.
  @param  dest   - The destination of the edge.
  @retval        - True if the edge exists.
  @retval        - False if the edge does not exist.
**/
bool EdgeExists(Vertex* vertex, unsigned int dest);

/**
  @brief  Checks if an edge exists between two given vertex ID's.
  @param  graph - The graph which contains the vertices and edges.
  @param  src   - The identifier of the source vertex.
  @param  dest  - The identifier of the destination vertex.
  @retval       - True if the edge exists.
  @retval       - False if the edge does not exist.
**/
bool EdgeExistsBetweenVertices(const Graph* graph, unsigned int src,
  unsigned int dest);

/**
  @brief Removes a specific edge from a vertex.
  @param vertex - The vertex which contains the edge.
  @param dest   - The destination of the edge.
  @retval       - SUCCESS_REMOVING_EDGE if the edge was removed.
  @retval       - INVALID_VERTEX if the vertex is invalid.
  @retval       - EDGE_DOES_NOT_EXIST if the edge does not exist.
  @retval       - UNDEFINED_ERROR if edge was not found.
**/
int RemoveEdge(Vertex* vertex, unsigned int dest);

/**
  @brief Removes all outgoing edges from a vertex.
  @param vertex - The vertex from which to remove all outgoing edges.
  @retval       - SUCCESS_REMOVING_OUTGOING_EDGES if all edges were removed.
  @retval       - VERTEX_EDGES_NULL if the vertex or its edges are NULL.
  @retval       - ERROR_REMOVING_EDGE if there was an error removing an edge.
**/
int RemoveOutgoingEdges(Vertex* vertex);

/**
  @brief Removes edges pointing to a specific vertex from a vertex's edge
         list.
  @param vertex         - The vertex from which to remove edges.
  @param targetVertexId - The ID of the vertex to which the edges point.
  @retval               - SUCCESS_REMOVING_EDGES if all edges were removed.
  @retval               - ERROR_REMOVING_EDGE if there was an error removing
                          an edge.
**/
int RemoveEdgesPointingTo(Vertex* vertex, unsigned int targetVertexId);

/**
  @brief Removes all incoming edges to a specified vertex in the graph.
  @param graph    - The graph from which to remove incoming edges.
  @param vertexId - The ID of the vertex for which to remove incoming edges.
  @retval         - SUCCESS_REMOVING_INCOMING_EDGES if all edges were removed.
  @retval         - INVALID_GRAPH if the graph is NULL.
  @retval         - ERROR_REMOVING_EDGE if there was an error removing an edge.
**/
int RemoveIncomingEdges(const Graph* graph, unsigned int vertexId);

#endif  // !EDGES_H
