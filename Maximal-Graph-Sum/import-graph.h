/**
 *  @file      import-graph.h
 *  @brief     Function definitions for importing graphs from a file.
 *  @author    Enrique Rodrigues
 *  @date      13.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 */
#ifndef IMPORT_GRAPH_H
#define IMPORT_GRAPH_H

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

#define END_MARKER 0xFFFFFFFF
#define END_VERTICES_MARKER 0xFFFFFFFE

#define MAX_LINE_LENGTH (1 * 1024 * 1024)  // 1MB
#define MAX_FILE_SIZE_MB 200
#define MAX_FILE_SIZE (MAX_FILE_SIZE_MB * 1024 * 1024)

#define ERROR_OPENING_FILE -1
#define MAX_FILE_SIZE_EXCEEDED -2
#define ERROR_ALLOCATING_MEMORY -3
#define SUCCESS_IMPORTING 0

#define INVALID_INPUT -1

#include <stdlib.h>

#include "graph.h"

/**
 *  @brief  Imports a graph from a text file with a CSV style format.
 *  @param  filename - The name of the text file.
 *  @param  graph    - The graph where we will place the data.
 *  @retval          - `SUCCESS_IMPORTING` if the graph was imported
 *                      successfully.
 *  @retval          - `ERROR_OPENING_FILE` if the file could not be opened.
 *  @retval          - `MAX_FILE_SIZE_EXCEEDED` if the max file size was
 *                     exceeded.
 *  @retval          - `ERROR_ALLOCATING_MEMORY` if there was an error
 *                     allocating memory.
 */
int ImportGraph(const char* filename, Graph* graph);

/**
 *  @brief  Loads a graph from a binary file.
 *  @param  filename - The name of the binary file.
 *  @retval          -
 */
Graph* LoadGraph(const char* filename);

#endif  // !IMPORT_GRAPH_H
