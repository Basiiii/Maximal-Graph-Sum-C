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
#include "vertices.h"

#pragma comment(lib, "Maximal-Graph-Sum.lib")

int main() {
  clock_t start;
  clock_t end;
  double cpu_time_used;

  Sleep(200);

  // Start the clock
  start = clock();

  Graph* graph = CreateGraph(15, 60);

  for (int i = 0; i < 15; i++) {
    CreateAddVertex(graph, i);
  }

  // for (int i = 0; i < 2000000; i++) {
  //   if (i < 3) {
  //     CreateAddEdge(FindVertex(graph, i), 2, 5);
  //   }
  //   else {
  //     CreateAddEdge(FindVertex(graph, i - 2), i, 5);
  //   }
  // }

  // End the clock
  end = clock();

  // Calculate the CPU time used
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  DisplayGraph(graph);

  FreeGraph(graph);

  // Print the CPU time used
  printf("\n\nCPU time used: %f seconds\n", cpu_time_used);

  return 0;
}
