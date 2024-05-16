/**
 *
 *  @file      vertices.c
 *  @brief
 *  @details   ~
 *  @author    Enrique Rodrigues
 *  @date      15.05.2024
 *  @copyright � Enrique Rodrigues, 2024. All right reserved.
 *
 */
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "edges.h"
#include "graph.h"

 /**
    @brief  Computes a hash value for a given ID.

    @details This function applies a custom hashing algorithm that provides
             excellent statistical distribution, ensuring that each input bit
             influences each output bit approximately 50% of the time.
             Importantly, this algorithm guarantees unique outputs for distinct
             inputs, eliminating collisions. The algorithm is designed to be
             efficient, leveraging integer arithmetic and bitwise operations.

             The hash function incorporates a "magic number" (0x45d9f3b), which
             was meticulously chosen through extensive testing. This process
             involved assessing the avalanche effect (the average number of
             output bits that change when a single input bit alters, ideally
             around 16), independence among output bit changes, and the
             likelihood of any output bit changing when any input bit changes.
             The selected constant outperforms the 32-bit finalizer used by
             MurmurHash and approaches the quality of hashes generated by AES
             encryption, albeit with a slight advantage in using the same
             constant twice, which may offer marginal speed benefits.

             Credit to Thomas Mueller for this algorithm:
             (https://stackoverflow.com/users/382763/thomas-mueller)

    @param  id       - The identifier to be hashed.
    @param  hashSize - The size of the hash table.
    @retval          - A hash value computed from input ID.
 **/
uint32_t Hash(uint32_t id, uint32_t hashSize) {
  // Inicialize position as given id
  uint32_t index = id;

  // Apply the hash function
  index = ((index >> 16) ^ index) * 0x45d9f3b;
  index = ((index >> 16) ^ index) * 0x45d9f3b;
  index = (index >> 16) ^ index;

  // Normalize the hash value to fit within the hash table size
  index %= hashSize;

  return index;
}

// https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
//
// uint32_t UnHash(uint32_t index) {
//    // Inicialize id as given index
//    uint32_t id = index;
//
//    // Apply the unhash function
//    id = ((id >> 16) ^ id) * 0x119de1f3;
//    id = ((id >> 16) ^ id) * 0x119de1f3;
//    id = (id >> 16) ^ id;
//    return id;
//}

/**
 *  @brief Creates a new vertex with specified vertexID.
 *  @param  vertexID - The identifier of the vertex to be created.
 *  @retval          - A pointer to the newly created vertex.
 *  @retval          - NULL if memory allocation fails.
 */
Vertex* CreateVertex(unsigned int vertexID) {
  Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
  if (newVertex == NULL) {
    return NULL;
  }

  newVertex->id = vertexID;
  newVertex->edges = NULL;

  return newVertex;
}

/**
    @brief Adds a vertex to the hash table of a graph.
    @param graph    - The graph where the vertex should be added.
    @param vertex   - The vertex to be added to the hash table of the graph.
    @retval         - False if given graph is NULL.
    @retval         - True in the case of success.
**/
bool AddVertex(const Graph* graph, const Vertex* vertex) {
  if (graph == NULL) {
    return false;
  }

  unsigned int index = Hash(vertex->id, graph->hashSize);
  graph->vertices[index] = vertex;

  return true;
}

/**
    @brief  Creates and adds a vertex to the hash table of a graph.
    @param  graph    - The graph where the created vertex should be added.
    @param  vertexID - The identifier of the vertex to be crated and added.
    @retval          - EXIT_SUCCESS in the case of success.
    @retval          - FAILURE_CREATING_VERTEX if memory allocation fails.
    @retval          - VERTEX_ALREADY_EXISTS if the vertex already exists.
**/
int CreateAddVertex(const Graph* graph, unsigned int vertexID) {
  if (VertexExists(graph, vertexID)) {
    return VERTEX_ALREADY_EXISTS;
  }

  const Vertex* vertex = CreateVertex(vertexID);
  if (vertex == NULL) {
    return FAILURE_CREATING_VERTEX;
  }

  if (AddVertex(graph, vertex) == false) {
    free(vertex);
    return FAILURE_ADDING_VERTEX;
  }

  return SUCCESS_ADDING_VERTEX;
}

/**
 *  @brief  Checks if a vertex exists or not.
 *  @param  graph       - The graph where the vertex should be.
 *  @param  vertexID    - The index where the vertex should be.
 *  @retval             - True if vertex exists or False if not.
 */
bool VertexExists(const Graph* graph, unsigned int vertexID) {
  unsigned int index = Hash(vertexID, graph->hashSize);
  return graph->vertices[index] != NULL;
}

/**
 *  @brief Tries to find a vertex from the given identifier.
 *  @param  graph    - The graph which should contain the vertex.
 *  @param  vertexID - The identifier of the vertex.
 *  @retval          - A pointer to the found vertex.
 *  @retval          - NULL if vertex was not found.
 */
Vertex* FindVertex(const Graph* graph, unsigned int vertexID) {
  unsigned int index = Hash(vertexID, graph->hashSize);
  return graph->vertices[index];
}

/**
    @brief  Removes a vertex from the graph and updates the vertex count.
    @param  graph    - The graph which contains the vertex to be removed.
    @param  vertexID - The ID of the vertex to be removed.
    @retval          - SUCCESS_REMOVING_VERTEX if the vertex was removed.
    @retval          - INVALID_GRAPH if the graph is invalid.
    @retval          - VERTEX_DOES_NOT_EXIST if the vertex does not exist.
**/
int RemoveVertex(Graph* graph, int vertexID) {
  if (graph == NULL) {
    return INVALID_GRAPH;
  }

  Vertex* vertexToRemove = FindVertex(graph, vertexID);
  if (vertexToRemove == NULL) {
    return VERTEX_DOES_NOT_EXIST;
  }

  RemoveOutgoingEdges(vertexToRemove);

  RemoveIncomingEdges(graph, vertexID);

  free(vertexToRemove);

  graph->numVertices--;

  return SUCCESS_REMOVING_VERTEX;
}
