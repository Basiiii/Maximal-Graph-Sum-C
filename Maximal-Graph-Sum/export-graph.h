#ifndef EXPORT_GRAPH_H
#define EXPORT_GRAPH_H

#include "graph.h"

/**
 *  @brief Saves a graph to a binary file.
 *  @param graph    - The graph which contains the data.
 *  @param filename - The name of the new binary file.
 */
void SaveGraph(const Graph* graph, const char* filename);

#endif  // !EXPORT_GRAPH_H
