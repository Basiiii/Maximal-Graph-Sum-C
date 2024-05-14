/**
 *
 *  @file      search.c
 *  @brief
 *  @details   ~
 *  @author    Enrique Rodrigues
 *  @date      14.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 *
 */
#include "search.h"

#include <stdio.h>

#include "graph.h"

// Function to initialize a path
Path* CreatePath(int length) {
  Path* path = (Path*)malloc(sizeof(Path));
  if (path == NULL) {
    return NULL;
  }
  path->nodes = (int*)malloc(length * sizeof(int));
  if (path->nodes == NULL) {
    free(path);
    return NULL;
  }
  path->length = 0;
  return path;
}

// Function to copy a path
Path* CopyPath(const Path* source) {
  Path* newPath = CreatePath(source->length);
  if (newPath == NULL) {
    return NULL;
  }
  newPath->length = source->length;
  for (int i = 0; i < source->length; i++) {
    newPath->nodes[i] = source->nodes[i];
  }
  return newPath;
}

// Function to add a node to a path
void AddToPath(Path* path, int node) {
  path->nodes[path->length] = node;
  path->length++;
}

// Function to print a path
void PrintPath(const Path* path) {
  for (int i = 0; i < path->length; i++) {
    printf("%d ", path->nodes[i]);
  }
  printf("\n");
}

// Function to free memory allocated for a path
void FreePath(Path* path) {
  free(path->nodes);
  free(path);
}

void DFS(Graph* graph, Vertex* vertex, bool visited[], Path* currentPath) {
  if (vertex == NULL) {
    return;
  }
  visited[vertex->vertex] = true;
  AddToPath(currentPath, vertex->vertex);

  Edge* edge = vertex->edges;
  while (edge != NULL) {
    if (!visited[edge->dest]) {
      DFS(graph, FindVertex(graph, edge->dest), visited, currentPath);
    }
    edge = edge->next;
  }

  // After exploring all neighbors, backtrack by removing the current vertex
  // from the path
  RemoveFromPath(currentPath);

  // Reset the visited status of the current vertex to allow it to be revisited
  // in other paths
  visited[vertex->vertex] = false;
}

// Function to remove the last node from a path
void RemoveFromPath(Path* path) {
  if (path->length > 0) {
    path->length--;  // Decrement the length of the path to remove the last node
  }
}

// Wrapper function for DFS traversal to find all possible paths
void DepthFirstSearch(Graph* graph, int start) {
  if (graph == NULL) {
    return;
  }
  bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
  if (visited == NULL) {
    return;
  }
  for (int i = 0; i < graph->numVertices; ++i) {
    visited[i] = false;
  }

  Vertex* startVertex = FindVertex(graph, start);
  if (startVertex != NULL) {
    printf("Started DFS from vertex %d\n", start);
    Path* currentPath =
        CreatePath(1);  // Initialize the path with the starting vertex
    AddToPath(currentPath,
              startVertex->vertex);  // Add the starting vertex to the path
    DFS(graph, startVertex, visited, currentPath);
    FreePath(currentPath);  // Free the path after DFS is done
  }

  free(visited);
}

//
// void DFS(Graph* graph, Vertex* vertex, bool visited[]) {
//  if (vertex == NULL) {
//    return;
//  }
//  visited[vertex->vertex] = true;
//  printf("%d ", vertex->vertex);
//
//  Edge* edge = vertex->edges;
//  while (edge != NULL) {
//    if (!visited[edge->dest]) {
//      DFS(graph, FindVertex(graph, edge->dest), visited);
//    }
//    edge = edge->next;
//  }
//}
//
// void DepthFirstSearch(Graph* graph, int start) {
//  if (graph == NULL) {
//    return;
//  }
//  bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
//  if (visited == NULL) {
//    return;
//  }
//  for (int i = 0; i < graph->numVertices; ++i) {
//    visited[i] = false;
//  }
//
//  Vertex* startVertex = FindVertex(graph, start);
//  if (startVertex != NULL) {
//    DFS(graph, startVertex, visited);
//  }
//
//  free(visited);
//}

void DFSUtil(Graph* graph, int src, int dest, bool* visited, int* path,
             int* pathIndex) {
  visited[src] = true;
  path[*pathIndex] =
      src;         // Dereference pathIndex to get the value it points to
  (*pathIndex)++;  // Increment the value pointed to by pathIndex

  if (src == dest) {
    // Destination reached, print the path
    for (int i = 0; i < pathIndex; i++) {
      printf("%d ", path[i]);
    }
    printf("\n");
  } else {
    // Explore neighbors
    Edge* edge = graph->vertices->edges;
    while (edge != NULL) {
      if (!visited[edge->dest]) {
        DFSUtil(graph, edge->dest, dest, visited, path, pathIndex);
      }
      edge = edge->next;
    }
  }

  // Backtrack
  pathIndex--;
  visited[src] = false;
}

void FindAllPaths(Graph* graph, int src, int dest) {
  bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
  int* path = (int*)calloc(graph->numVertices, sizeof(int));
  int pathIndex = 0;

  DFSUtil(graph, src, dest, visited, path, &pathIndex);

  free(visited);
  free(path);
}
