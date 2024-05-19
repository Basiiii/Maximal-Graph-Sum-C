#include "search.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertices.h"

// Helper function to perform DFS and find all paths
void DFS(const Graph* graph, unsigned int src, unsigned int dest, bool* visited,
  unsigned int* path, unsigned int pathIndex, unsigned int*** paths,
  unsigned int* numPaths, unsigned int* pathCapacity) {
  // Mark the current node as visited and store it in the path
  visited[src] = true;
  path[pathIndex] = src;
  pathIndex++;

  // If we reached the destination, save the current path
  if (src == dest) {
    // Allocate more space for paths if needed
    if (*numPaths == *pathCapacity) {
      *pathCapacity *= 2;
      *paths = (unsigned int**)realloc(*paths,
        (*pathCapacity) * sizeof(unsigned int*));
    }
    // Copy the current path to the list of paths
    (*paths)[*numPaths] =
      (unsigned int*)malloc((pathIndex + 1) * sizeof(unsigned int));
    memcpy((*paths)[*numPaths], path, pathIndex * sizeof(unsigned int));
    (*paths)[*numPaths][pathIndex] =
      UINT_MAX;  // Sentinel value to mark the end
    (*numPaths)++;
  }
  else {
    // Recur for all the vertices adjacent to the current vertex
    Vertex* vertex = FindVertex(graph, src);
    if (vertex) {
      Edge* edge = vertex->edges;
      while (edge != NULL) {
        if (!visited[edge->dest]) {
          DFS(graph, edge->dest, dest, visited, path, pathIndex, paths,
            numPaths, pathCapacity);
        }
        edge = edge->next;
      }
    }
  }

  // Backtrack: remove the current vertex from the path and mark it as unvisited
  pathIndex--;
  visited[src] = false;
}

unsigned int** FindAllPaths(const Graph* graph, unsigned int src,
  unsigned int dest, unsigned int* numPaths) {
  // Initialize variables
  *numPaths = 0;
  unsigned int pathCapacity = 10;
  unsigned int** paths =
    (unsigned int**)malloc(pathCapacity * sizeof(unsigned int*));
  bool* visited = (bool*)calloc(graph->hashSize, sizeof(bool));
  unsigned int* path =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));
  unsigned int pathIndex = 0;

  // Perform DFS
  DFS(graph, src, dest, visited, path, pathIndex, &paths, numPaths,
    &pathCapacity);

  // Clean up
  free(visited);
  free(path);

  return paths;
}

void FreePaths(unsigned int** paths, unsigned int numPaths) {
  for (unsigned int i = 0; i < numPaths; i++) {
    free(paths[i]);
  }
  free(paths);
}

void PrintPaths(unsigned int** paths, unsigned int numPaths) {
  for (unsigned int i = 0; i < numPaths; i++) {
    printf("Path %u: ", i + 1);
    for (unsigned int j = 0; paths[i][j] != UINT_MAX; j++) {
      printf("%u ", paths[i][j]);
    }
    printf("\n");
  }
}
