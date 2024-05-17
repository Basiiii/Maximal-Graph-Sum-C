/**

    @file      main.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "edges.h"
#include "graph.h"
#include "import-graph.h"
#include "vertices.h"

#pragma comment(lib, "Maximal-Graph-Sum.lib")

int main() {
  clock_t start;
  clock_t end;
  double cpu_time_used;

  Sleep(200);

  // Start the clock
  start = clock();

  Graph* graph = CreateGraph(5000000);

  printf("\n%u\n", graph->numVertices);

  ImportGraph("C:\\Users\\user\\Desktop\\test.txt", graph);

  // End the clock
  end = clock();

  // Calculate the CPU time used
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  // DisplayGraph(graph);

  printf("\n%u\n", graph->numVertices);

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

  // Print the CPU time used
  printf("\n\nCPU time used: %f seconds\n", cpu_time_used);

  return 0;
}
