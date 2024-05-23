/**
 *
 *  @file      import-graph.c
 *  @brief     Function implementations for importing a graph from a file.
 *  @author    Enrique Rodrigues
 *  @date      8.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS

#include "import-graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edges.h"
#include "graph.h"
#include "vertices.h"

/**
 *  @brief  Helper function to calculate the size of the file.
 *  @param  file - A pointer to the file whose size we will check.
 *  @retval      - The size of the file.
 */
static size_t GetFileSize(FILE* file) {
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

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
int ImportGraph(const char* filename, Graph* graph) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    return ERROR_OPENING_FILE;
  }

  size_t fileSize = GetFileSize(file);
  if (fileSize > MAX_FILE_SIZE) {
    fclose(file);
    return MAX_FILE_SIZE_EXCEEDED;
  }

  char* fileContent = malloc(fileSize + 1);
  if (!fileContent) {
    fclose(file);
    return ERROR_ALLOCATING_MEMORY;
  }

  fread(fileContent, 1, fileSize, file);
  fileContent[fileSize] = '\0';

  fclose(file);

  char* line = malloc(MAX_LINE_LENGTH);
  if (!line) {
    free(fileContent);
    return ERROR_ALLOCATING_MEMORY;
  }

  const char* lineStart = fileContent;
  const char* lineEnd = NULL;

  while ((lineEnd = strchr(lineStart, '\n')) != NULL) {
    size_t lineLength = lineEnd - lineStart;
    if (lineLength >= MAX_LINE_LENGTH) {
      lineStart = lineEnd + 1;
      continue;
    }
    snprintf(line, MAX_LINE_LENGTH, "%.*s", (int)lineLength, lineStart);
    line[lineLength] = '\0';

    lineStart = lineEnd + 1;

    char* saveptr = line;
    const char* token = strtok_s(line, ";", &saveptr);
    if (!token) {
      continue;
    }
    unsigned int vertexID = atoi(token);

    CreateAddVertex(graph, vertexID);
    Vertex* vertex = FindVertex(graph, vertexID);

    while ((token = strtok_s(NULL, ";", &saveptr)) != NULL) {
      unsigned int destID = atoi(token);
      if (!(token = strtok_s(NULL, ";", &saveptr))) {
        break;
      }
      unsigned int weight = atoi(token);

      CreateAddVertex(graph, destID);
      CreateAddEdge(vertex, destID, weight);
    }
  }

  free(line);
  free(fileContent);

  return SUCCESS_IMPORTING;
}

/**
 *  @brief  Creates the graph definition based on data on the file.
 *  @param  file - The file which holds the data.
 *  @retval      - A pointer to Graph or NULL in the event of error.
 */
static Graph* CreateGraphFromFile(FILE* file) {
  unsigned int hashSize;
  fread(&hashSize, sizeof(unsigned int), 1, file);

  Graph* graph = malloc(sizeof(Graph));
  if (graph == NULL) {
    return NULL;
  }

  graph->vertices = calloc(hashSize, sizeof(Vertex*));
  if (graph->vertices == NULL) {
    free(graph);
    return NULL;
  }
  graph->numVertices = 0;
  graph->hashSize = hashSize;

  return graph;
}

/**
 *  @brief  Reads vertices and edges from a binary file and populates the graph.
 *  @param  graph - The graph to be populated.
 *  @param  file  - A pointer to the binary file.
 *  @retval       - `EXIT_SUCCESS` on success, `EXIT_FAILURE` on failure.
 */
static int ReadVerticesAndEdgesFromFile(Graph* graph, FILE* file) {
  for (unsigned int i = 0; i < graph->hashSize; ++i) {
    unsigned int vertexId;

    while (fread(&vertexId, sizeof(unsigned int), 1, file) == 1) {
      if (vertexId == END_MARKER) {
        break;
      }

      CreateAddVertex(graph, vertexId);
      Vertex* vertex = FindVertex(graph, vertexId);

      unsigned int dest;
      unsigned int weight;
      while (fread(&dest, sizeof(unsigned int), 1, file) == 1 &&
             dest != END_MARKER &&
             fread(&weight, sizeof(unsigned int), 1, file) == 1) {
        CreateAddEdge(vertex, dest, weight);
      }
    }
  }

  return EXIT_SUCCESS;
}

/**
 *  @brief  Loads a graph from a binary file.
 *  @param  filename - The name of the binary file.
 *  @retval          - A pointer to Graph with the data inside of it or NULL in
 *                     the event of an error.
 */
Graph* LoadGraph(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if (!file) {
    return NULL;
  }

  Graph* graph = CreateGraphFromFile(file);
  if (graph == NULL) {
    fclose(file);
    return NULL;
  }

  if (ReadVerticesAndEdgesFromFile(graph, file) != EXIT_SUCCESS) {
    fclose(file);
    return NULL;
  }

  fclose(file);

  return graph;
}
