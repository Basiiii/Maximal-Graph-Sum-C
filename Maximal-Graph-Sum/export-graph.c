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

#define END_MARKER 0xFFFFFFFF
#define END_VERTICES_MARKER 0xFFFFFFFE

#define ERROR_OPENING_FILE -1
#define ERROR_WRITING_HEADER -2
#define ERROR_WRITING_VERTICES -3

#include <stdio.h>

#include <cstdlib>

#include "graph-structure.h"

static int WriteHeaderToBinFile(FILE* file, const Graph* graph) {
  // Write number of vertices to file
  size_t header = fwrite(&graph->numVertices, sizeof(unsigned int), 1, file);
  if (header != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  // Write size of hash table to file
  header = fwrite(&graph->hashSize, sizeof(unsigned int), 1, file);
  if (header != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int WriteVertexIDToFile(FILE* file, const Vertex* vertex) {
  if (fwrite(&vertex->id, sizeof(unsigned int), 1, file) != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int WriteEdgeToFile(FILE* file, const Edge* edge) {
  if (fwrite(&edge->dest, sizeof(unsigned int), 1, file) != 1 ||
    fwrite(&edge->weight, sizeof(unsigned int), 1, file) != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int WriteEndMarkerToFile(FILE* file) {
  if (fwrite(END_MARKER, sizeof(unsigned int), 1, file) != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int WriteVerticesToBinFile(FILE* file, const Graph* graph) {
  for (unsigned int i = 0; i < graph->hashSize; ++i) {
    Vertex* vertex = graph->vertices[i];
    while (vertex) {
      WriteVertexIDToFile(file, vertex);

      Edge* edge = vertex->edges;
      while (edge) {
        WriteEdgeToFile(file, edge);
        edge = edge->next;
      }

      WriteEndMarkerToFile(file);

      vertex = vertex->next;
    }
  }
  return 0;  // Indicate success
}

static int WriteEndMarkersToFile(FILE* file) {
  if (fwrite(END_VERTICES_MARKER, sizeof(unsigned int), 1, file) != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int SaveGraph(const Graph* graph, const char* filename) {
  FILE* file = fopen(filename, "wb");
  if (!file) {
    return ERROR_OPENING_FILE;
  }

  if (WriteHeaderToBinFile(file, graph) == EXIT_FAILURE) {
    return ERROR_WRITING_HEADER;
  }

  if (WriteVerticesToBinFile(file, graph) == EXIT_FAILURE) {
    return ERROR_WRITING_VERTICES;
  }

  WriteEndMarkersToFile(file);

  fclose(file);
}
