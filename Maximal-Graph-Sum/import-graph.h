/**
 *  @file      import-graph.h
 *  @brief
 *  @details   ~
 *  @author    Enrique Rodrigues
 *  @date      13.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 */
#ifndef IMPORT_GRAPH_H
#define IMPORT_GRAPH_H

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

#include <stdlib.h>

#include "graph.h"

int ImportGraphWhole(const char* filename, Graph* graph);

int ImportGraphLBL(const char* filename, Graph* graph);

/**
 *  @brief  Loads a graph from a binary file.
 *  @param  filename - The name of the binary file.
 *  @retval          -
 */
Graph* LoadGraph(const char* filename);

#endif  // !IMPORT_GRAPH_H
