/**

    @file      main.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include <stdio.h>

#include "graph.h"
#include "import-graph.h"
#include "search.h"

int main() {
  // Create a new graph
  Graph* graph = CreateGraph();

  ImportGraphLine(graph, "file.csv");

  DisplayGraph(graph);

  return 0;
}
