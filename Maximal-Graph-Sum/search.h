#ifndef SEARCH_H
#define SEARCH_H

#include <stdbool.h>

#include "graph.h"

typedef struct PathNode {
  unsigned int* vertices;
  unsigned int* weights;
  unsigned int length;
  struct PathNode* next;
} PathNode;

void DFS(const Graph* graph, unsigned int src, unsigned int dest, bool* visited,
  unsigned int* pathVertices, unsigned int* pathWeights,
  unsigned int pathIndex, PathNode** paths, unsigned int* numPaths,
  unsigned int* pathCapacity);

PathNode* FindAllPaths(const Graph* graph, unsigned int src, unsigned int dest,
  unsigned int* numPaths);

void FreePaths(PathNode* paths);

void PrintPaths(PathNode* paths);

unsigned int CalculatePathSum(const PathNode* path);

#endif  // SEARCH_H
