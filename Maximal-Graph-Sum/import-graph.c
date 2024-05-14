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

#include "graph.h"

static void ProcessEdge(Graph* graph, int srcIndex, int destIndex, int weight) {
  // Add vertex if it doesn't exist
  AddVertexIfNotExists(graph, srcIndex);
  AddVertexIfNotExists(graph, destIndex);

  // Add edge from the source vertex to the destination vertex
  AddEdge(graph, srcIndex, destIndex, weight);
}

void ImportGraph(Graph* graph, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Failed to open file.\n");
    return;
  }

  int srcIndex = 0;
  int destIndex = 0;
  int weight = 0;
  int c;

  // Loop until end of file
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      ProcessEdge(graph, srcIndex, destIndex, weight);
      srcIndex++;     // Move to the next source vertex
      destIndex = 0;  // Reset destination index
      weight = 0;     // Reset weight
    } else if (c == ';') {
      ProcessEdge(graph, srcIndex, destIndex, weight);
      destIndex++;  // Move to the next destination vertex
      weight = 0;   // Reset weight
    } else {
      weight = weight * 10 + (c - '0');  // Accumulate weight
    }
  }

  // Process the last element of the last row
  if (weight != 0) {
    ProcessEdge(graph, srcIndex, destIndex, weight);
  }

  fclose(file);
}

static void ProcessNumbers(Graph* graph, int num1, int num2) {
  // Add vertices if they don't exist
  AddVertexIfNotExists(graph, num1);
  AddVertexIfNotExists(graph, num2);

  // TODO: update num vertices here

  // Connect the vertices
  AddEdgeIfNotExists(graph, num1, num2, 1);  // TODO: weight
}

void ImportGraphLine(Graph* graph, const char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Failed to open file.\n");
    return;
  }

  int prevNum = -1;  // Previous number
  int num;
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      // Newline character encountered, reset prevNum
      prevNum = -1;
    } else if (c >= '0' && c <= '9') {
      // Read a number
      ungetc(c, file);  // Put the digit back to read the number correctly
      fscanf(file, "%d", &num);
      if (prevNum != -1) {
        // Process numbers and connect vertices
        ProcessNumbers(graph, prevNum, num);
      }
      prevNum = num;
    }
  }

  fclose(file);
}
