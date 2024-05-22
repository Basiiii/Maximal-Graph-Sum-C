/**
 *
 *  @file      export-graph.c
 *  @brief     Function implementations for exporting data to a file.
 *  @author    Enrique Rodrigues
 *  @date      21.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS

#include "export-graph.h"

#include <stdio.h>
#include <stdlib.h>

#include "graph-structure.h"

/**
 *  @brief  Exports a graph to a CSV file format.
 *  @param  filename - The name of the CSV file.
 *  @param  graph    - The graph to be exported.
 *  @retval          - `EXIT_SUCCESS` on success, or an error code
 *                     indicating failure.
 */
int ExportGraph(const char* filename, const Graph* graph) {
  FILE* file = fopen(filename, "w");
  if (!file) {
    return ERROR_OPENING_FILE;
  }

  for (unsigned int i = 0; i < graph->hashSize; ++i) {
    Vertex* vertex = graph->vertices[i];
    while (vertex) {
      fprintf(file, "%u", vertex->id);  // Write the vertex ID
      Edge* edge = vertex->edges;
      while (edge) {
        fprintf(file, ";%u;%u", edge->dest,
                edge->weight);  // Write the destination and weight
        edge = edge->next;
      }
      fprintf(file, "\n");  // Newline for the next vertex
      vertex = vertex->next;
    }
  }

  fclose(file);

  return EXIT_SUCCESS;
}

static int WriteHeaderToBinFile(FILE* file, const Graph* graph) {
  // Write size of hash table to file
  size_t header = fwrite(&graph->hashSize, sizeof(unsigned int), 1, file);
  if (header != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int WriteVertexIDToFile(FILE* file, const Vertex* vertex) {
  if (file == NULL) {
    return EXIT_FAILURE;
  }

  if (fwrite(&vertex->id, sizeof(unsigned int), 1, file) != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int WriteEdgeToFile(FILE* file, const Edge* edge) {
  if (file == NULL) {
    return EXIT_FAILURE;
  }

  if (fwrite(&edge->dest, sizeof(unsigned int), 1, file) != 1 ||
      fwrite(&edge->weight, sizeof(unsigned int), 1, file) != 1) {
    fclose(file);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

static int WriteEndMarkerToFile(FILE* file) {
  if (file == NULL) {
    return EXIT_FAILURE;
  }
  unsigned int endMarker = END_MARKER;
  if (fwrite(&endMarker, sizeof(unsigned int), 1, file) != 1) {
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

/**
 *  @param     graph - A pointer to the graph to be saved.
 *  @param     filename - The name of the file where the graph will be saved.
 *  @retval    EXIT_SUCCESS on success.
 *  @retval    ERROR_OPENING_FILE if the file cannot be opened.
 *  @retval    ERROR_WRITING_HEADER if there is an error writing the header.
 *  @retval    ERROR_WRITING_VERTICES if there is an error writing the vertices.
 *  @retval    ERROR_WRITING_MARKER if there is an error writing the end marker.
 */
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

  if (WriteEndMarkerToFile(file) == EXIT_FAILURE) {
    return ERROR_WRITING_MARKER;
  }

  fclose(file);

  return EXIT_SUCCESS;
}
