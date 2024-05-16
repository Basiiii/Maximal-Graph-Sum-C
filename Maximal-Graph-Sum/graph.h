/**

    @file      graph.h
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#ifndef GRAPH_H
#define GRAPH_H

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

#include "graph-error-codes.h"

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
            number and a linked list of all edges.
**/
typedef struct Vertex {
  unsigned int id;  // Vertex id (identification)
  Edge* edges;      // Start of linked list of adjacent vertices
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

/**
 *  @brief  Creates a new graph with the specified number of vertices and hash
 *          table size.
 *  @param  numVertices - The initial number of vertices in the graph.
 *  @param  hashSize    - The size of the hash table used to store vertices.
 *  @retval             - A pointer to the newly created graph.
 *  @retval             - NULL if memory allocation fails.
 */
Graph* CreateGraph(unsigned int numVertices, unsigned int hashSize);

/**
    @brief Displays the graph in a text format to stdout.
    @param graph - The graph to be displayed.
**/
void DisplayGraph(const Graph* graph);

/**
    @brief Frees a given graph from memory.
    @param graph - The graph to be freed.
**/
void FreeGraph(Graph* graph);

#endif  // !GRAPH_H
