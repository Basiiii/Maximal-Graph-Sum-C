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
#include "graph-structure.h"

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
