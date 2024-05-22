/**
 *
 *  @file      search.c
 *  @brief     Function implementations for search algorithms to find all paths
               and calculate the sum of all edges in a path.
 *  @author    Enrique Rodrigues
 *  @date      22.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 *
 */
#include "search.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertices.h"

 /**
  * @brief Adds the current path to the list of paths in the context.
  *
  * @param context - Pointer to the DFSContext containing the current path and
  *                  paths list.
  * @return bool - True if the path is successfully added, false otherwise.
  */
bool AddPath(DFSContext* context) {
  if (*context->numPaths == *context->pathCapacity) {
    *context->pathCapacity *= 2;
    PathNode** paths = (PathNode**)realloc(
      *context->paths, *context->pathCapacity * sizeof(PathNode*));
    if (paths != NULL) {
      *context->paths = paths;
    }
    else {
      return false;  // Memory reallocation failed
    }
  }

  // Allocate memory for a new path
  PathNode* newPath = (PathNode*)malloc(sizeof(PathNode));
  if (newPath == NULL) {
    return false;  // Memory allocation for newPath failed
  }

  // Allocate memory for the vertices and weights of the new path
  newPath->vertices =
    (unsigned int*)malloc((context->pathIndex + 1) * sizeof(unsigned int));
  newPath->weights =
    (unsigned int*)malloc((context->pathIndex + 1) * sizeof(unsigned int));
  if (newPath->vertices == NULL || newPath->weights == NULL) {
    free(newPath->vertices);  // Free allocated memory for vertices if any
    free(newPath->weights);   // Free allocated memory for weights if any
    free(newPath);            // Free the PathNode itself
    return false;  // Memory allocation for vertices or weights failed
  }

  // Copy the current path data to the new path node
  memcpy(newPath->vertices, context->pathVertices,
    (context->pathIndex + 1) * sizeof(unsigned int));
  memcpy(newPath->weights, context->pathWeights,
    (context->pathIndex + 1) * sizeof(unsigned int));
  newPath->length = context->pathIndex + 1;
  newPath->next = NULL;

  // Add the new path to the paths list
  if (*context->paths == NULL) {
    *context->paths = newPath;
  }
  else {
    PathNode* current = *context->paths;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newPath;
  }

  (*context->numPaths)++;
  return true;  // Path successfully added
}

/**
 * @brief Marks the current vertex as unvisited for backtracking.
 *
 * @param context - Pointer to the DFSContext containing the visited status of
 *                  vertices.
 * @param vertex  - The vertex to be marked as unvisited.
 */
void Backtrack(DFSContext* context, unsigned int vertex) {
  context->visited[vertex] = false;
}

/**
 * @brief Recursively explores all adjacent vertices of the current vertex.
 *
 * @param context - Pointer to the DFSContext containing the graph and traversal
 * state.
 * @param src - The current source vertex being explored.
 * @param dest - The destination vertex to which paths are being found.
 * @return bool - True if all traversals complete successfully, false otherwise.
 */
bool TraverseEdges(DFSContext* context, unsigned int src, unsigned int dest) {
  Vertex* vertex = FindVertex(context->graph, src);
  if (!vertex) return true;  // No edges to traverse, return success

  Edge* edge = vertex->edges;
  bool success = true;

  while (edge != NULL) {
    if (!context->visited[edge->dest]) {
      context->pathWeights[context->pathIndex] = edge->weight;
      context->pathIndex++;
      success = DepthFirstSearch(context, edge->dest, dest);
      context->pathIndex--;
      if (!success) break;  // Stop further traversal if failure occurs
    }
    edge = edge->next;
  }

  return success;
}

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
bool DepthFirstSearch(DFSContext* context, unsigned int src,
  unsigned int dest) {
  context->visited[src] = true;
  context->pathVertices[context->pathIndex] = src;

  bool success = true;

  if (src == dest) {
    success = AddPath(context);
  }
  else {
    success = TraverseEdges(context, src, dest);
  }

  Backtrack(context, src);
  return success;
}

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
  unsigned int* numPaths) {
  *numPaths = 0;
  unsigned int pathCapacity = 10;
  PathNode* paths = NULL;
  bool* visited = (bool*)calloc(graph->hashSize, sizeof(bool));
  unsigned int* pathVertices =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));
  unsigned int* pathWeights =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));

  DFSContext context = { .graph = graph,
                        .pathVertices = pathVertices,
                        .pathWeights = pathWeights,
                        .visited = visited,
                        .pathIndex = 0,
                        .paths = &paths,
                        .numPaths = numPaths,
                        .pathCapacity = &pathCapacity };

  bool success = DepthFirstSearch(&context, src, dest);

  if (!success) {
    // Free all paths if there was an error
    FreePaths(paths);
    paths = NULL;
    *numPaths = 0;
  }

  free(visited);
  free(pathVertices);
  free(pathWeights);

  return paths;
}

/**
 * @brief Frees the memory allocated for the list of paths.
 *
 * @param paths - Pointer to the head of the linked list of paths to be freed.
 */
void FreePaths(PathNode* paths) {
  while (paths != NULL) {
    PathNode* next = paths->next;
    free(paths->vertices);
    free(paths->weights);
    free(paths);
    paths = next;
  }
}

/**
 * @brief Prints all paths stored in the linked list of paths.
 *
 * @param paths - Pointer to the head of the linked list of paths to be printed.
 */
void PrintPaths(PathNode* paths) {
  unsigned int pathIndex = 1;
  while (paths != NULL) {
    printf("Path %u: ", pathIndex++);
    for (unsigned int i = 0; i < paths->length - 1; i++) {
      printf("%u -(%u)-> ", paths->vertices[i], paths->weights[i]);
    }
    printf("%u", paths->vertices[paths->length - 1]);

    // Calculate and print the sum of the current path
    unsigned int sum = CalculatePathSum(paths);
    printf(" (Total Weight: %u)\n", sum);

    paths = paths->next;
  }
}

/**
 * @brief Calculates the sum of the weights of the edges in the given path.
 *
 * @param path - Pointer to the PathNode containing the path.
 * @return unsigned int - The total weight of the path.
 */
unsigned int CalculatePathSum(const PathNode* path) {
  unsigned int sum = 0;
  for (unsigned int i = 0; i < path->length - 1; i++) {
    sum += path->weights[i];
  }
  return sum;
}
