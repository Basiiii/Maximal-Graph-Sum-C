#ifndef SEARCH_H
#define SEARCH_H

#include "graph.h"

/**
    @brief Finds all paths from source to destination.
    @param graph    - The graph to search paths in.
    @param src      - The source vertex ID.
    @param dest     - The destination vertex ID.
    @retval         - A dynamically allocated array of paths, where each path is
                     represented as a dynamically allocated array of vertex IDs.
**/
unsigned int** FindAllPaths(const Graph* graph, unsigned int src,
  unsigned int dest, unsigned int* numPaths);

/**
    @brief Frees the memory allocated for paths.
    @param paths    - The paths to be freed.
    @param numPaths - The number of paths.
**/
void FreePaths(unsigned int** paths, unsigned int numPaths);

/**
    @brief Prints all the paths stored in the paths array.
    @param paths    - The paths to be printed.
    @param numPaths - The number of paths.
**/
void PrintPaths(unsigned int** paths, unsigned int numPaths);

#endif  // SEARCH_H
