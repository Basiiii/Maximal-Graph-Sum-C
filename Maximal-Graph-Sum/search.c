#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertices.h"

// Helper function to perform DFS and find all paths
void DFS(const Graph* graph, unsigned int src, unsigned int dest, bool* visited,
  unsigned int* pathVertices, unsigned int* pathWeights,
  unsigned int pathIndex, PathNode** paths, unsigned int* numPaths,
  unsigned int* pathCapacity) {
  // Debug statement to trace function execution
  printf("DFS called with src: %u, dest: %u\n", src, dest);

  // Mark the current node as visited and store it in the path
  visited[src] = true;
  pathVertices[pathIndex] = src;

  // If we reached the destination, save the current path
  if (src == dest) {
    // Allocate more space for paths if needed
    if (*numPaths == *pathCapacity) {
      *pathCapacity *= 2;
      *paths = (PathNode*)realloc(*paths, *pathCapacity * sizeof(PathNode));
    }

    // Create a new PathNode for this path
    PathNode* newPath = (PathNode*)malloc(sizeof(PathNode));
    newPath->vertices =
      (unsigned int*)malloc((pathIndex + 1) * sizeof(unsigned int));
    newPath->weights =
      (unsigned int*)malloc((pathIndex + 1) * sizeof(unsigned int));
    memcpy(newPath->vertices, pathVertices,
      (pathIndex + 1) * sizeof(unsigned int));
    memcpy(newPath->weights, pathWeights,
      (pathIndex + 1) * sizeof(unsigned int));
    newPath->length = pathIndex + 1;
    newPath->next = NULL;

    // Add the new path to the list of paths
    if (*paths == NULL) {
      *paths = newPath;
    }
    else {
      PathNode* current = *paths;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = newPath;
    }

    (*numPaths)++;
  }
  else {
    // Recur for all the vertices adjacent to the current vertex
    Vertex* vertex = FindVertex(graph, src);
    if (vertex) {
      Edge* edge = vertex->edges;
      while (edge != NULL) {
        if (!visited[edge->dest]) {
          pathWeights[pathIndex] = edge->weight;
          DFS(graph, edge->dest, dest, visited, pathVertices, pathWeights,
            pathIndex + 1, paths, numPaths, pathCapacity);
        }
        edge = edge->next;
      }
    }
  }

  // Backtrack: mark the current vertex as unvisited
  visited[src] = false;

  // Debug statement to trace backtracking
  printf("Backtracking from vertex: %u\n", src);
}

PathNode* FindAllPaths(const Graph* graph, unsigned int src, unsigned int dest,
  unsigned int* numPaths) {
  // Initialize variables
  *numPaths = 0;
  unsigned int pathCapacity = 10;
  PathNode* paths = NULL;
  bool* visited = (bool*)calloc(graph->hashSize, sizeof(bool));
  unsigned int* pathVertices =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));
  unsigned int* pathWeights =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));

  // Perform DFS
  DFS(graph, src, dest, visited, pathVertices, pathWeights, 0, &paths, numPaths,
    &pathCapacity);

  // Clean up
  free(visited);
  free(pathVertices);
  free(pathWeights);

  return paths;
}

void FreePaths(PathNode* paths) {
  while (paths != NULL) {
    PathNode* next = paths->next;
    free(paths->vertices);
    free(paths->weights);
    free(paths);
    paths = next;
  }
}

void PrintPaths(PathNode* paths) {
  unsigned int pathIndex = 1;
  while (paths != NULL) {
    printf("Path %u: ", pathIndex++);
    for (unsigned int i = 0; i < paths->length - 1; i++) {
      printf("%u -(%u)-> ", paths->vertices[i], paths->weights[i]);
    }
    printf("%u\n", paths->vertices[paths->length - 1]);
    paths = paths->next;
  }
}
