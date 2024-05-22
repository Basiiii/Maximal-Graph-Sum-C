/**
 *  @file      graph-structure.h
 *  @brief     The structure definitions of the graph.
 *  @author    Enrique Rodrigues
 *  @date      21.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 */
#ifndef GRAPH_STRUCTURE_H
#define GRAPH_STRUCTURE_H

/**
  @struct Edge
  @brief  Structure of an edge in the graph which contains a destination
          vertex, weight and pointer to the next edge in the linked list.
**/
typedef struct Edge {
  unsigned int dest;    // Destination vertex
  unsigned int weight;  // Weight of the edge
  struct Edge* next;    // Pointer to the next edge in the list
} Edge;

/**
  @struct Vertex
  @brief  Structure of a vertex of a graph which contains an identification
          number, a linked list of all edges and a next position to traverse
          to the next vertices.

  @details This structure contains a next field to traverse to other vertices
           which were hashed to the same position of the hash table. This
           solution is a simple yet effective way to handle collisions in the
           hash table.
**/
typedef struct Vertex {
  unsigned int id;      // Vertex id (identification)
  Edge* edges;          // Start of linked list of adjacent vertices
  struct Vertex* next;  // Next vertex in the hash position
} Vertex;

/**
  @struct Graph
  @brief  Structure of a graph built with a hash table for vertices and linked
          lists for edges.
**/
typedef struct Graph {
  unsigned int numVertices;  // Current number of vertices of the graph
  unsigned int hashSize;     // Current size of hash table
  Vertex** vertices;         // Hash table of vertices
} Graph;

#endif  // !GRAPH_STRUCTURE_H
