/**
 *
 *  @file      export-graph.c
 *  @brief
 *  @details   ~
 *  @author    Enrique Rodrigues
 *  @date      21.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "graph.h"

/**
 *  @brief Saves a graph to a binary file.
 *  @param graph    - The graph which contains the data.
 *  @param filename - The name of the new binary file.
 */
void SaveGraph(const Graph* graph, const char* filename) {
  FILE* file = fopen(filename, "wb");
  if (!file) {
    perror("Failed to open file");
    return;
  }

  // Write the number of vertices and hash size
  fwrite(&graph->numVertices, sizeof(unsigned int), 1, file);
  fwrite(&graph->hashSize, sizeof(unsigned int), 1, file);

  // Iterate through the hash table
  for (unsigned int i = 0; i < graph->hashSize; ++i) {
    Vertex* vertex = graph->vertices[i];
    while (vertex) {
      // Write vertex ID
      fwrite(&vertex->id, sizeof(unsigned int), 1, file);

      // Write edges
      Edge* edge = vertex->edges;
      while (edge) {
        fwrite(&edge->dest, sizeof(unsigned int), 1, file);
        fwrite(&edge->weight, sizeof(unsigned int), 1, file);
        edge = edge->next;
      }

      // Write a special marker to mark the end of the edge list
      unsigned int endMarker = 0xFFFFFFFF;
      fwrite(&endMarker, sizeof(unsigned int), 1, file);

      vertex = vertex->next;
    }
  }

  fclose(file);
}
