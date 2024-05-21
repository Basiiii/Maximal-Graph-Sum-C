/**
 *
 *  @file      import-graph.c
 *  @brief
 *  @details   ~
 *  @author    Enrique Rodrigues
 *  @date      8.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edges.h"
#include "graph.h"
#include "vertices.h"

#define MAX_LINE_LENGTH (1 * 1024 * 1024)  // 1MB
#define MAX_FILE_SIZE_MB 200
#define MAX_FILE_SIZE (MAX_FILE_SIZE_MB * 1024 * 1024)

#define ERROR_OPENING_FILE -1
#define MAX_FILE_SIZE_EXCEEDED -2
#define ERROR_ALLOCATING_MEMORY -3
#define SUCCESS_IMPORTING 0

#define INVALID_INPUT -1

#include "import-graph.h"

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
 *  @retval          -
 */
int ImportGraphWhole(const char* filename, Graph* graph) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    perror("Failed to open file");
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

static Graph* createGraphFromFile(FILE* file) {
  unsigned int numVertices, hashSize;
  fread(&numVertices, sizeof(unsigned int), 1, file);
  fread(&hashSize, sizeof(unsigned int), 1, file);

  Graph* graph = malloc(sizeof(Graph));
  graph->vertices = calloc(hashSize, sizeof(Vertex*));
  graph->numVertices = numVertices;
  graph->hashSize = hashSize;

  return graph;
}

static void readVerticesFromFile(Graph* graph, FILE* file) {
  unsigned int i = 0;
  while (fread(&i, sizeof(unsigned int), 1, file) == 1 && i != 0xFFFFFFFE) {
    Vertex* vertex = malloc(sizeof(Vertex));
    vertex->id = i;
    vertex->edges = NULL;
    vertex->next = NULL;
    graph->vertices[i] = vertex;
  }
}

static void readEdgesFromFile(Vertex* vertex, FILE* file) {
  unsigned int edgeDest, edgeWeight;
  while (fread(&edgeDest, sizeof(unsigned int), 1, file) == 1 &&
    edgeDest != 0xFFFFFFFF) {
    fread(&edgeWeight, sizeof(unsigned int), 1, file);
    Edge* edge = malloc(sizeof(Edge));
    edge->dest = edgeDest;
    edge->weight = edgeWeight;
    edge->next = vertex->edges;
    vertex->edges = edge;
  }
}

Graph* LoadGraph(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if (!file) {
    perror("Failed to open file");
    return NULL;
  }

  Graph* graph = createGraphFromFile(file);
  if (!graph) {
    fclose(file);
    return NULL;
  }

  readVerticesFromFile(graph, file);
  fclose(file);

  return graph;
}
