/**
 *  @file      export-graph.h
 *  @brief     Function definitions for exporting graphs to files.
 *  @author    Enrique Rodrigues
 *  @date      22.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 */
#ifndef EXPORT_GRAPH_H
#define EXPORT_GRAPH_H

#include "graph.h"

#define END_MARKER 0xFFFFFFFF
#define END_VERTICES_MARKER 0xFFFFFFFE

#define ERROR_OPENING_FILE -1
#define ERROR_WRITING_HEADER -2
#define ERROR_WRITING_VERTICES -3
#define ERROR_WRITING_MARKER -4

/**
 *  @brief  Exports a graph to a CSV file format.
 *  @param  graph    - The graph to be exported.
 *  @param  filename - The name of the CSV file.
 *  @retval          - `EXIT_SUCCESS` on success, or an error code
 *                     indicating failure.
 */
int ExportGraph(const char* filename, const Graph* graph);

/**
 *  @param     graph - A pointer to the graph to be saved.
 *  @param     filename - The name of the file where the graph will be saved.
 *  @retval    EXIT_SUCCESS on success.
 *  @retval    ERROR_OPENING_FILE if the file cannot be opened.
 *  @retval    ERROR_WRITING_HEADER if there is an error writing the header.
 *  @retval    ERROR_WRITING_VERTICES if there is an error writing the vertices.
 *  @retval    ERROR_WRITING_MARKER if there is an error writing the end marker.
 */
int SaveGraph(const Graph* graph, const char* filename);

#endif  // !EXPORT_GRAPH_H
