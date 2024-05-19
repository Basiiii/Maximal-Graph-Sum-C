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

#define INVALID_INPUT -1

#include "import-graph.h"

static size_t GetFileSizeCustom(FILE* file) {
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

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

  return 0;  // Success
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
