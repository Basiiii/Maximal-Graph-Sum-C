/**
 *  @file      search.h
 *  @brief     Function definitions for search algorithms to find all paths and
               calculate the sum of all edges in a path.
 *  @author    Enrique Rodrigues
 *  @date      22.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 */
#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>

#include "graph.h"

 /**
     @struct DFSContext
     @brief  Variables that give context for the DFS function to work.
 **/
typedef struct DFSContext {
  const Graph* graph;
  unsigned int* pathVertices;
  unsigned int* pathWeights;
  bool* visited;
  unsigned int pathIndex;
  struct PathNode** paths;
  unsigned int* numPaths;
  unsigned int* pathCapacity;
} DFSContext;

/**
    @struct PathNode
    @brief A linked list structure which holds a path.
**/
typedef struct PathNode {
  unsigned int* vertices;
  unsigned int* weights;
  unsigned int length;
  struct PathNode* next;
} PathNode;

/**
 * @brief Adds the current path to the list of paths in the context.
 *
 * @param context - Pointer to the DFSContext containing the current path and
 *                  paths list.
 * @return bool - True if the path is successfully added, false otherwise.
 */
bool AddPath(DFSContext* context);

/**
 * @brief Marks the current vertex as unvisited for backtracking.
 *
 * @param context - Pointer to the DFSContext containing the visited status of
 *                  vertices.
 * @param vertex  - The vertex to be marked as unvisited.
 */
void Backtrack(DFSContext* context, unsigned int vertex);

/**
 * @brief Recursively explores all adjacent vertices of the current vertex.
 *
 * @param context - Pointer to the DFSContext containing the graph and traversal
 * state.
 * @param src - The current source vertex being explored.
 * @param dest - The destination vertex to which paths are being found.
 * @return bool - True if all traversals complete successfully, false otherwise.
 */
bool TraverseEdges(DFSContext* context, unsigned int src, unsigned int dest);

/**
 * @brief Performs Depth-First Search (DFS) on the graph from a given source to
 * a given destination.
 *
 * @param context - Pointer to the DFSContext containing the graph and traversal
 * state.
 * @param src - The source vertex from which DFS starts.
 * @param dest - The destination vertex to which paths are being found.
 * @return bool - True if the DFS completes successfully, false otherwise.
 */
bool DepthFirstSearch(DFSContext* context, unsigned int src, unsigned int dest);

/**
 * @brief Finds all paths from the source vertex to the destination vertex in
 * the graph.
 *
 * @param graph - Pointer to the graph.
 * @param src - The source vertex from which paths start.
 * @param dest - The destination vertex to which paths are being found.
 * @param numPaths - Pointer to store the number of paths found.
 * @return PathNode* - Pointer to the head of the linked list of paths.
 */
PathNode* FindAllPaths(const Graph* graph, unsigned int src, unsigned int dest,
  unsigned int* numPaths);

/**
 * @brief Frees the memory allocated for the list of paths.
 *
 * @param paths - Pointer to the head of the linked list of paths to be freed.
 */
void FreePaths(PathNode* paths);

/**
 * @brief Prints all paths stored in the linked list of paths.
 *
 * @param paths - Pointer to the head of the linked list of paths to be printed.
 */
void PrintPaths(PathNode* paths);

/**
 * @brief Calculates the sum of the weights of the edges in the given path.
 *
 * @param path - Pointer to the PathNode containing the path.
 * @return unsigned int - The total weight of the path.
 */
unsigned int CalculatePathSum(const PathNode* path);

#endif  // SEARCH_H
