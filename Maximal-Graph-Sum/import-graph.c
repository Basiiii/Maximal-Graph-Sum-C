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
static size_t GetFileSizeCustom(FILE* file) {
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
  // Open file
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR_OPENING_FILE;
  }

  // Get file size
  size_t fileSize = GetFileSizeCustom(file);
  if (fileSize > MAX_FILE_SIZE) {
    fclose(file);
    return MAX_FILE_SIZE_EXCEEDED;
  }

  // Read file content into memory
  char* fileContent = (char*)malloc(fileSize + 1);
  if (fileContent == NULL) {
    fclose(file);
    return ERROR_ALLOCATING_MEMORY;
  }

  fread(fileContent, 1, fileSize, file);
  fileContent[fileSize] = '\0';  // Null-terminate the content

  // Close file
  fclose(file);

  // Allocate memory for line buffer
  char* line = (char*)malloc(MAX_LINE_LENGTH);
  if (line == NULL) {
    free(fileContent);
    return ERROR_ALLOCATING_MEMORY;
  }

  // Process file content
  const char* lineStart = fileContent;
  const char* lineEnd = NULL;

  // Iterate over file
  while ((lineEnd = strchr(lineStart, '\n')) != NULL) {
    // Copy the line to a temporary buffer (to null-terminate it)
    size_t lineLength = lineEnd - lineStart;
    if (lineLength >= MAX_LINE_LENGTH) {
      // Line exceeds maximum length
      lineStart = lineEnd + 1;
      continue;
    }
    strncpy(line, lineStart, lineLength);
    line[lineLength] = '\0';  // Ensure null-termination
    lineStart = lineEnd + 1;

    // Tokenize line by semicolon
    char* saveptr = line;
    const char* token = strtok_s(line, ";", &saveptr);
    if (token == NULL) {
      continue;  // Empty line
    }
    unsigned int vertexID = atoi(token);

    // Create or add the vertex
    CreateAddVertex(graph, vertexID);
    Vertex* vertex = FindVertex(graph, vertexID);

    while ((token = strtok_s(NULL, ";", &saveptr)) != NULL) {
      unsigned int destID = atoi(token);
      if ((token = strtok_s(NULL, ";", &saveptr)) == NULL) {
        break;
      }
      unsigned int weight = atoi(token);

      CreateAddVertex(graph, destID);
      CreateAddEdge(vertex, destID, weight);
    }
  }

  // Cleanup
  free(line);
  free(fileContent);

  return SUCCESS_IMPORTING;
}

int ImportGraphLBL(const char* filename, Graph* graph) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR_OPENING_FILE;
  }

  size_t fileSize = GetFileSizeCustom(file);
  if (fileSize > MAX_FILE_SIZE) {
    fclose(file);
    return MAX_FILE_SIZE_EXCEEDED;
  }

  char* fileContent = (char*)malloc(fileSize + 1);
  if (fileContent == NULL) {
    fclose(file);
    return ERROR_ALLOCATING_MEMORY;
  }

  size_t bytesRead = fread(fileContent, 1, fileSize, file);
  fileContent[fileSize] = '\0';
  fclose(file);

  char* context = NULL;
  char* line = strtok_s(fileContent, "\n", &context);

  while (line != NULL) {
    size_t lineLength = strlen(line);
    if (lineLength >= MAX_LINE_LENGTH) {
      line = strtok_s(NULL, "\n", &context);
      continue;
    }

    char* saveptr = NULL;
    char* token = strtok_s(line, ";", &saveptr);
    if (token == NULL) {
      line = strtok_s(NULL, "\n", &context);
      continue;
    }

    unsigned int vertexID = atoi(token);
    CreateAddVertex(graph, vertexID);
    Vertex* vertex = FindVertex(graph, vertexID);

    while ((token = strtok_s(NULL, ";", &saveptr)) != NULL) {
      unsigned int destID = atoi(token);
      if ((token = strtok_s(NULL, ";", &saveptr)) == NULL) {
        break;
      }
      unsigned int weight = atoi(token);

      CreateAddVertex(graph, destID);
      CreateAddEdge(vertex, destID, weight);
    }

    line = strtok_s(NULL, "\n", &context);
  }

  free(fileContent);
  return 0;  // Success
}

/**
 *  @brief  Loads a graph from a binary file.
 *  @param  filename - The name of the binary file.
 *  @retval          -
 */
Graph* LoadGraph(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if (file == NULL) {
    return NULL;
  }

  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (graph == NULL) {
    fclose(file);
    return NULL;
  }

  // Read number of vertices and hash size
  fread(&graph->numVertices, sizeof(unsigned int), 1, file);
  fread(&graph->hashSize, sizeof(unsigned int), 1, file);

  // Allocate memory for hash table of vertices
  graph->vertices = (Vertex**)malloc(graph->hashSize * sizeof(Vertex*));
  if (graph->vertices == NULL) {
    fclose(file);
    free(graph);
    return NULL;
  }

  // Initialize hash table entries to NULL
  for (unsigned int i = 0; i < graph->hashSize; ++i) {
    graph->vertices[i] = NULL;
  }

  unsigned int vertexID;
  unsigned int dest;
  unsigned int weight;

  while (fread(&vertexID, sizeof(unsigned int), 1, file) == 1) {
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    if (vertex == NULL) {
      fclose(file);
      FreeGraph(graph);
      return NULL;
    }

    vertex->id = vertexID;
    vertex->edges = NULL;
    vertex->next = NULL;

    Vertex** bucket = &graph->vertices[Hash(vertexID, graph->hashSize)];
    if (*bucket == NULL) {
      *bucket = vertex;
    } else {
      vertex->next = *bucket;
      *bucket = vertex;
    }

    while (fread(&dest, sizeof(unsigned int), 1, file) == 1) {
      if (dest == 0xFFFFFFFF) {
        break;  // End of edge list
      }
      fread(&weight, sizeof(unsigned int), 1, file);

      Edge* edge = (Edge*)malloc(sizeof(Edge));
      if (edge == NULL) {
        fclose(file);
        FreeGraph(graph);
        return NULL;
      }

      edge->dest = dest;
      edge->weight = weight;

      edge->next = vertex->edges;
      vertex->edges = edge;
    }
  }

  fclose(file);
  return graph;
}
