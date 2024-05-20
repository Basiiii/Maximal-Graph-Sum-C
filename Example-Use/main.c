/**

    @file      main.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright � Enrique George Rodrigues, 2024. All right reserved.

**/
#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "dijkstra.h"
#include "edges.h"
#include "graph.h"
#include "import-graph.h"
#include "search.h"
#include "vertices.h"

#pragma comment(lib, "Maximal-Graph-Sum.lib")

int main() {
  clock_t start;
  clock_t end;
  double cpu_time_used;

  Sleep(200);

  // Start the clock
  start = clock();

  Graph* graph = CreateGraph(200);

  printf("\n%u\n", graph->numVertices);

  ImportGraphLBL("C:\\Users\\user\\Desktop\\test.txt", graph);

  // End the clock
  end = clock();

  // Calculate the CPU time used
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  DisplayGraph(graph);

  printf("\n%u\n", graph->numVertices);

  // Print the CPU time used
  printf("\n\nCPU time used: %f seconds\n", cpu_time_used);

  start = clock();

  unsigned int numPaths = 0;
  unsigned int** paths = FindAllPaths(graph, 2, 7, &numPaths);

  // End the clock
  end = clock();

  // Calculate the CPU time used
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Found %u paths from vertex 2 to vertex 7:\n", numPaths);
  PrintPaths(paths, numPaths);

  // Print the CPU time used
  printf("\n\nCPU time used in search: %f seconds\n", cpu_time_used);

  // Free allocated memory
  FreePaths(paths, numPaths);

  unsigned int src = 2;
  unsigned int dest = 7;

  unsigned int maxSum;
  unsigned int* path;
  unsigned int pathLength;

  start = clock();

  DijkstraMaxSum(graph, src, dest, &maxSum, &path, &pathLength);

  // End the clock
  end = clock();

  // Calculate the CPU time used
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  // Print the CPU time used
  printf("\n\nCPU time used in Dijkstra: %f seconds\n", cpu_time_used);

  if (pathLength > 0) {
    PrintMaxSumPath(path, pathLength, maxSum);
  }
  else {
    printf("No path found from vertex %u to vertex %u.\n", src, dest);
  }

  free(path);

  // printf("\n");
  // for (unsigned int i = 0; i < graph->hashSize; ++i) {
  //   int vertexCount = 0;
  //   Vertex* vertex = graph->vertices[i];
  //   while (vertex != NULL) {
  //     vertexCount++;
  //     vertex = vertex->next;
  //   }

  //  printf("Hash position %u has %d vertices.\n", i, vertexCount);
  //}

  FreeGraph(graph);

  return 0;
}
