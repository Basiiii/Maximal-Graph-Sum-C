/**

    @file      main.c
    @brief     Example program to showcase and test performance of the graph
               library.
    @details   This program showcases how to use the graph library and includes
               performance tests.
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "dijkstra.h"
#include "edges.h"
#include "export-graph.h"
#include "graph.h"
#include "import-graph.h"
#include "search.h"
#include "vertices.h"

#pragma comment(lib, "Maximal-Graph-Sum.lib")

int main() {
  // Variables used to measure time
  clock_t start;
  clock_t end;

#ifdef CREATE_ADD_VERTICES_TEST
  printf("Executing Create Add Vertices test...\n");

  unsigned int hashSize = 3000000;
  unsigned int numVertices = 1000000;

  Graph* graph = CreateGraph(hashSize);

  printf("Starting number of vertices: %u\n", graph->numVertices);

  start = clock();

  // Create and add one million vertices
  for (unsigned int i = 0; i < numVertices; i++) {
    CreateAddVertex(graph, i);
  }

  end = clock();

  printf("Ending number of vertices: %u\n", graph->numVertices);

  // Free Graph from memory
  FreeGraph(graph);

  // Calculate the CPU time used
  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used: %f seconds\n", cpuTimeUsed);

#endif  //  CREATE_ADD_VERTICES_TEST

#ifdef CREATE_ADD_EDGES_TEST
  printf("Executing Create Add Edges test...\n");

  unsigned int hashSize = 3000000;
  unsigned int numVertices = 1000000;
  unsigned int numEdges = 1000000;

  // Create a graph with the specified hash size
  Graph* graph = CreateGraph(hashSize);

  // Add vertices to the graph
  for (unsigned int i = 0; i < numVertices; i++) {
    if (CreateAddVertex(graph, i) != EXIT_SUCCESS) {
      printf("Error creating vertex for testing.\n");
      FreeGraph(graph);
      return 1;
    }
  }

  // Choose a specific vertex to add edges to
  unsigned int srcVertexId = 0;
  Vertex* srcVertex = FindVertex(graph, srcVertexId);
  if (srcVertex == NULL) {
    printf("Source vertex not found in the graph.\n");
    FreeGraph(graph);
    return 1;
  }

  // Begin Test
  printf("Vertices ready, beginning test.\n");

  // Start time measurement
  start = clock();

  // Create and add edges to the specified vertex
  for (unsigned int i = 0; i < numEdges; i++) {
    Edge* edge = CreateEdge(i, 1);
    AddEdgeToVertex(srcVertex, edge);
  }

  // End time measurement
  end = clock();

  // Calculate the CPU time used
  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used: %f seconds\n", cpuTimeUsed);

  // Verify the number of edges added
  unsigned int edgeCount = 0;
  Edge* edge = srcVertex->edges;
  while (edge != NULL) {
    edgeCount++;
    edge = edge->next;
  }
  printf("Number of edges added: %u\n", edgeCount);

  // Free Graph from memory
  FreeGraph(graph);

#endif  // CREATE_ADD_EDGE_TEST

#ifdef IMPORT_TEST
  printf("Executing import test...\n");

  // Create graph
  Graph* graph = CreateGraph(1000000);

  // Start clock
  start = clock();

  // Import from text file
  ImportGraphWhole("C:\\Users\\Basi\\Desktop\\test.txt", graph);

  // End clock
  end = clock();

  // Result
  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used during import: %f seconds\n", cpuTimeUsed);

  // Free Graph from memory
  FreeGraph(graph);

#endif

  /*Graph* graph = CreateGraph(3000);

  ImportGraphWhole("C:\\Users\\user\\Desktop\\test.txt", graph);

  DisplayGraph(graph);

  SaveGraph(graph, "test");

  FreeGraph(graph);*/

  printf("\n\n\n\n");

  Graph* graph2 = LoadGraph("test");

  DisplayGraph(graph2);

  FreeGraph(graph2);

  // Graph* graph2 = CreateGraph(500);
  // LoadGraph("test");

  // FreeGraph(graph);

  // unsigned int numPaths = 0;
  // unsigned int** paths = FindAllPaths(graph, 2, 6, &numPaths);

  //// End the clock
  // end = clock();

  //// Calculate the CPU time used
  // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  // printf("Found %u paths from vertex 2 to vertex 6:\n", numPaths);
  // PrintPaths(paths, numPaths);

  //// Print the CPU time used
  // printf("\n\nCPU time used in search: %f seconds\n", cpu_time_used);

  //// Free allocated memory
  // FreePaths(paths, numPaths);

  // unsigned int src = 2;
  // unsigned int dest = 6;

  // unsigned int minSum;
  // unsigned int* path;
  // unsigned int pathLength;

  // start = clock();

  // DijkstraShortestPath(graph, src, dest, &minSum, &path, &pathLength);

  //// End the clock
  // end = clock();

  //// Calculate the CPU time used
  // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  //// Print the CPU time used
  // printf("\n\nCPU time used in Dijkstra: %f seconds\n", cpu_time_used);

  // if (pathLength > 0) {
  //   PrintShortestPath(path, pathLength, minSum);
  // }
  // else {
  //   printf("No path found from vertex %u to vertex %u.\n", src, dest);
  // }

  // free(path);

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

  // FreeGraph(graph);

  return 0;
}
