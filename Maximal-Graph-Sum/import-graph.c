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
#include <time.h>

#include "edges.h"
#include "graph.h"
#include "vertices.h"

#define MAX_LINE_LENGTH (1 * 1024 * 1024)  // 1MB
#define MAX_FILE_SIZE_MB 200
#define MAX_FILE_SIZE (MAX_FILE_SIZE_MB * 1024 * 1024)

#define INVALID_INPUT -1

static size_t GetFileSize(FILE* file) {
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  return size;
}

int ImportGraph(const char* filename, Graph* graph) {
  clock_t start, end;
  double duration;

  // Open file
  start = clock();
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    perror("Failed to open file");
    return INVALID_INPUT;
  }
  end = clock();
  duration = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time to open file: %.2f seconds\n", duration);

  // Get file size
  start = clock();
  size_t fileSize = GetFileSize(file);
  end = clock();
  duration = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time to get file size: %.2f seconds\n", duration);

  if (fileSize > MAX_FILE_SIZE) {
    fclose(file);
    fprintf(stderr, "File size exceeds maximum limit\n");
    return INVALID_INPUT;
  }

  // Read file content into memory
  start = clock();
  char* fileContent = (char*)malloc(fileSize + 1);
  if (fileContent == NULL) {
    fclose(file);
    perror("Failed to allocate memory");
    return INVALID_INPUT;
  }

  size_t bytesRead = fread(fileContent, 1, fileSize, file);
  fileContent[fileSize] = '\0';  // Null-terminate the content
  end = clock();
  duration = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time to read file content: %.2f seconds\n", duration);

  // Close file
  fclose(file);

  // Allocate memory for line buffer
  start = clock();
  char* line = (char*)malloc(MAX_LINE_LENGTH);
  if (line == NULL) {
    free(fileContent);
    perror("Failed to allocate memory for line buffer");
    return INVALID_INPUT;
  }
  end = clock();
  duration = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time to allocate line buffer: %.2f seconds\n", duration);

  // Process file content
  start = clock();
  char* lineStart = fileContent;
  char* lineEnd = NULL;
  double totalLineProcessingTime = 0;
  double totalTokenProcessingTime = 0;

  while ((lineEnd = strchr(lineStart, '\n')) != NULL) {
    // Copy the line to a temporary buffer (to null-terminate it)
    clock_t lineStartClock = clock();
    size_t lineLength = lineEnd - lineStart;
    if (lineLength >= MAX_LINE_LENGTH) {
      // Line exceeds maximum length
      lineStart = lineEnd + 1;
      continue;
    }
    strncpy(line, lineStart, lineLength);
    line[lineLength] = '\0';  // Ensure null-termination
    lineStart = lineEnd + 1;
    clock_t lineEndClock = clock();
    totalLineProcessingTime +=
      (double)(lineEndClock - lineStartClock) / CLOCKS_PER_SEC;

    // Tokenize line by semicolon
    clock_t tokenStartClock = clock();
    char* saveptr;
    char* token = strtok_s(line, ";", &saveptr);
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
    clock_t tokenEndClock = clock();
    totalTokenProcessingTime +=
      (double)(tokenEndClock - tokenStartClock) / CLOCKS_PER_SEC;
  }

  end = clock();
  duration = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Total time to process file content: %.2f seconds\n", duration);
  printf("Total time for line processing: %.2f seconds\n",
    totalLineProcessingTime);
  printf("Total time for token processing: %.2f seconds\n",
    totalTokenProcessingTime);

  // Cleanup
  free(line);
  free(fileContent);

  return 0;  // Success
}

// int ImportGraph(const char* filename, Graph* graph) {
//   FILE* file = fopen(filename, "r");
//   if (file == NULL) {
//     perror("Failed to open file");
//     return INVALID_INPUT;
//   }
//
//   size_t fileSize = GetFileSize(file);
//
//   if (fileSize > MAX_FILE_SIZE) {
//     fclose(file);
//     fprintf(stderr, "File size exceeds maximum limit\n");
//     return INVALID_INPUT;
//   }
//
//   char* fileContent = (char*)malloc(fileSize + 1);
//   if (fileContent == NULL) {
//     fclose(file);
//     perror("Failed to allocate memory");
//     return INVALID_INPUT;
//   }
//
//   size_t bytesRead = fread(fileContent, 1, fileSize, file);
//   /*if (bytesRead != fileSize) {
//     free(fileContent);
//     fclose(file);
//     perror("Failed to read file");
//     return INVALID_INPUT;
//   }*/
//
//   fileContent[fileSize] = '\0';  // Null-terminate the content
//
//   // Process file content
//   char* line = (char*)malloc(MAX_LINE_LENGTH);
//   if (line == NULL) {
//     free(fileContent);
//     fclose(file);
//     perror("Failed to allocate memory for line buffer");
//     return INVALID_INPUT;
//   }
//
//   char* lineStart = fileContent;
//   char* lineEnd = NULL;
//
//   while ((lineEnd = strchr(lineStart, '\n')) != NULL) {
//     // Copy the line to a temporary buffer (to null-terminate it)
//     size_t lineLength = lineEnd - lineStart;
//     if (lineLength >= MAX_LINE_LENGTH) {
//       // Line exceeds maximum length
//       lineStart = lineEnd + 1;
//       continue;
//     }
//     strncpy(line, lineStart, lineLength);
//     line[lineLength] = '\0';  // Ensure null-termination
//
//     // Move to the next line
//     lineStart = lineEnd + 1;
//
//     // Split line by semicolon
//     char* token;
//     token = strtok(line, ";");
//
//     // First token is the vertex ID
//     if (token == NULL) {
//       continue;  // Empty line
//     }
//     unsigned int vertexID = atoi(token);
//     token = strtok(NULL, ";");
//
//     // Create or add the vertex
//     CreateAddVertex(graph, vertexID);
//
//     // Process remaining tokens as edges and weights
//     while (token != NULL) {
//       unsigned int destID = atoi(token);
//       token = strtok(NULL, ";");
//       if (token == NULL) {
//         break;
//       }
//       unsigned int weight = atoi(token);
//       token = strtok(NULL, ";");
//
//       CreateAddVertex(graph, destID);
//       CreateAddEdge(FindVertex(graph, vertexID), destID, weight);
//     }
//   }
//
//   free(line);
//   free(fileContent);
//   fclose(file);
//
//   return 0;  // Success
// }
