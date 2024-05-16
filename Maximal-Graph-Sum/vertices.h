/**

    @file      vertices.h
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      16.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#ifndef VERTICES_H
#define VERTICES_H

#include <stdbool.h>
#include <stdint.h>

#include "graph.h"

#define MIN_LOAD_FACTOR 0.1
#define MAX_LOAD_FACTOR 0.5

#define DEFAULT_HASH_TABLE_SIZE 100

/**
   @brief  Computes a hash value for a given ID.

   @param  id       - The identifier to be hashed.
   @param  hashSize - The size of the hash table.
   @retval          - A hash value computed from input ID.
**/
uint32_t Hash(uint32_t id, uint32_t hashSize);

/**
 *  @brief Creates a new vertex with specified vertexID.
 *  @param  vertexID - The identifier of the vertex to be created.
 *  @retval          - A pointer to the newly created vertex. NULL if memory
 *                     allocation fails.
 */
Vertex* CreateVertex(unsigned int vertexID);

/**
    @brief Adds a vertex to the hash table of a graph.
    @param graph    - The graph where the vertex should be added.
    @param vertex   - The vertex to be added to the hash table of the graph.
    @retval         - False if given graph is NULL.
    @retval         - True in the case of success.
**/
bool AddVertex(const Graph* graph, const Vertex* vertex);

/**
    @brief  Creates and adds a vertex to the hash table of a graph.
    @param  graph    - The graph where the created vertex should be added.
    @param  vertexID - The identifier of the vertex to be crated and added.
    @retval          - EXIT_SUCCESS in the case of success.
    @retval          - FAILURE_CREATING_VERTEX if memory allocation fails.
    @retval          - VERTEX_ALREADY_EXISTS if the vertex already exists.
**/
int CreateAddVertex(const Graph* graph, unsigned int vertexID);

/**
 *  @brief  Checks if a vertex exists or not.
 *  @param  graph       - The graph where the vertex should be.
 *  @param  vertexID    - The index where the vertex should be.
 *  @retval             - True if vertex exists or False if not.
 */
bool VertexExists(const Graph* graph, unsigned int vertexID);

/**
 *  @brief Tries to find a vertex from the given identifier.
 *  @param  graph    - The graph which should contain the vertex.
 *  @param  vertexID - The identifier of the vertex.
 *  @retval          - A pointer to the found vertex.
 *  @retval          - NULL if vertex was not found.
 */
Vertex* FindVertex(const Graph* graph, unsigned int vertexID);

/**
    @brief  Removes a vertex from the graph and updates the vertex count.
    @param  graph    - The graph which contains the vertex to be removed.
    @param  vertexID - The ID of the vertex to be removed.
    @retval          - SUCCESS_REMOVING_VERTEX if the vertex was removed.
    @retval          - INVALID_GRAPH if the graph is invalid.
    @retval          - VERTEX_DOES_NOT_EXIST if the vertex does not exist.
**/
int RemoveVertex(Graph* graph, int vertexID);

#endif  // !VERTICES_H
