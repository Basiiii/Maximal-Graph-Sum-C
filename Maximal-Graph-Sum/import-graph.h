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

#include "graph.h"

void ImportGraph(Graph* graph, const char* filename);
void ImportGraphLine(Graph* graph, const char* filename);

#endif  // !IMPORT_GRAPH_H
