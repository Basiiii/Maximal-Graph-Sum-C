/**

    @file      main.c
    @brief     Example program to showcase and test performance and
               functionality of the graph library.
    @details   This program showcases the use the graph library and includes
               performance tests.
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include <Windows.h>
#include <stdio.h>
#include <time.h>

#include "dijkstra.h"
#include "edges.h"
#include "export-graph.h"
#include "graph.h"
#include "import-graph.h"
#include "search.h"
#include "vertices.h"

/* ============================= */
/* Define Default file locations */
/* ============================= */
// #define USE_DESKTOP // Define this if you have the files on your Desktop
#ifdef USE_DESKTOP
#define DEFAULT_USERS_FILE "C:\\Users\\"
#define WINDOWS_USER_NAME "user\\"
#define DEFAULT_USER_DIR DEFAULT_USERS_FILE WINDOWS_USER_NAME
#define DEFAULT_LOCATION DEFAULT_USER_DIR "Desktop\\"
#else
#define DEFAULT_LOCATION ""
#endif

#define DEFAULT_IMPORT_FILE_NAME DEFAULT_LOCATION "test.txt"
#define DEFAULT_EXPORT_FILE_NAME DEFAULT_LOCATION "export.txt"
#define DEFAULT_SAVE_FILE_NAME DEFAULT_LOCATION "save.dat"
#define DEFAULT_LOAD_FILE_NAME DEFAULT_SAVE_FILE_NAME
#define DEFAULT_FIND_ALL_PATHS_FILE_NAME DEFAULT_LOCATION "find-all.txt"

/* ================================== */
/* Define Default file specifications */
/* ================================== */
#define DEFAULT_HASH_SIZE 2000
#define FIND_ALL_PATHS_FILE_HASH_SIZE 50
#define ONE_MILLION_TEST_HASH_SIZE 2000000
#define ONE_MILLION_TEST_NUM_VERTICES 1000000
#define ONE_MILLION_TEST_NUM_EDGES 1000000

/* ============== */
/* Generic errors */
/* ============== */
#define UNKNOWN_ERROR -100

/* ==================================== */
/* Define the tests you wish to execute */
/* ==================================== */
// #define CREATE_ADD_VERTICES_TEST
// #define CREATE_ADD_EDGES_TEST
// #define IMPORT_TEST
// #define EXPORT_TEST
// #define SAVE_TEST
// #define LOAD_TEST
// #define FIND_ALL_PATHS_TEST

/* =================== */
/* Include the library */
/* =================== */
#pragma comment(lib, "Maximal-Graph-Sum.lib")

int main() {
  // Variables used to measure time
  clock_t start;
  clock_t end;

#ifdef CREATE_ADD_VERTICES_TEST

  printf("\n\nExecuting Create Add Vertices test...\n");

  unsigned int numVertices = ONE_MILLION_TEST_NUM_VERTICES;
  Graph* graph = CreateGraph(ONE_MILLION_TEST_HASH_SIZE);

  printf("Starting number of vertices: %u\n", graph->numVertices);
  start = clock();

  // Create and add one million vertices
  for (unsigned int i = 0; i < numVertices; i++) {
    CreateAddVertex(graph, i);
  }

  end = clock();
  printf("Ending number of vertices: %u\n", graph->numVertices);

  // Free Graph from memory
  FreeGraph(graph);

  // Calculate the CPU time used
  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used: %f seconds\n", cpuTimeUsed);

#endif  //  CREATE_ADD_VERTICES_TEST

#ifdef CREATE_ADD_EDGES_TEST

  printf("\n\nExecuting Create Add Edges test...\n");

  unsigned int hashSize = ONE_MILLION_TEST_HASH_SIZE;
  unsigned int numVertices = ONE_MILLION_TEST_NUM_VERTICES;
  unsigned int numEdges = ONE_MILLION_TEST_NUM_EDGES;
  Graph* graph = CreateGraph(hashSize);

  // Add vertices to the graph
  for (unsigned int i = 0; i < numVertices; i++) {
    if (CreateAddVertex(graph, i) != EXIT_SUCCESS) {
      printf("Error creating vertex for testing.\n");
      FreeGraph(graph);
      return 1;
    }
  }

  // Choose a specific vertex to add edges to
  unsigned int srcVertexId = 0;
  Vertex* srcVertex = FindVertex(graph, srcVertexId);
  if (srcVertex == NULL) {
    printf("Source vertex not found in the graph.\n");
    FreeGraph(graph);
    return 1;
  }

  // Begin Test
  printf("Vertices ready, beginning test.\n");
  start = clock();

  // Create and add edges to the specified vertex
  for (unsigned int i = 0; i < numEdges; i++) {
    Edge* edge = CreateEdge(i, 1);
    AddEdgeToVertex(srcVertex, edge);
  }

  // End test
  end = clock();
  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used: %f seconds\n", cpuTimeUsed);

  // Verify the number of edges added
  unsigned int edgeCount = 0;
  Edge* edge = srcVertex->edges;
  while (edge != NULL) {
    edgeCount++;
    edge = edge->next;
  }
  printf("Number of edges added: %u\n", edgeCount);

  // Free Graph from memory
  FreeGraph(graph);

#endif  // CREATE_ADD_EDGE_TEST

#ifdef IMPORT_TEST

  printf("\n\nExecuting import test...\n");
  Graph* graph = CreateGraph(DEFAULT_HASH_SIZE);
  const char* location = DEFAULT_IMPORT_FILE_NAME;

  // Start test
  start = clock();

  int res = ImportGraph(location, graph);

  // End test
  end = clock();

  // Error control
  if (res == EXIT_SUCCESS) {
    printf("Success.\n");
  }
  else {
    switch (res) {
    case ERROR_OPENING_FILE:
      printf("Error opening file.\n");
      exit(ERROR_OPENING_FILE);
    case MAX_FILE_SIZE_EXCEEDED:
      printf("Max file size exceeded.\n");
      exit(MAX_FILE_SIZE_EXCEEDED);
    case ERROR_ALLOCATING_MEMORY:
      printf("Error allocating memory.\n");
      exit(ERROR_ALLOCATING_MEMORY);
    default:
      printf("Unknown error occured.\n");
      exit(UNKNOWN_ERROR);
    }
  }

  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used during import: %f seconds\n", cpuTimeUsed);
  FreeGraph(graph);

#endif

#ifdef EXPORT_TEST

  printf("\n\nExecuting export test...\n");
  Graph* graph = CreateGraph(DEFAULT_HASH_SIZE);
  if (ImportGraph(DEFAULT_IMPORT_FILE_NAME, graph) != EXIT_SUCCESS) {
    printf("Error importing graph.");
    exit(EXIT_FAILURE);
  }

  // Start test
  start = clock();

  int res = ExportGraph(DEFAULT_EXPORT_FILE_NAME, graph);

  // End test
  end = clock();

  // Error control
  if (res == EXIT_SUCCESS) {
    printf("Success.\n");
  }
  else {
    printf("Error creating file.\n");
    FreeGraph(graph);
    exit(EXIT_FAILURE);
  }

  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used during export: %f seconds\n", cpuTimeUsed);
  FreeGraph(graph);

#endif

#ifdef SAVE_TEST

  printf("\n\nExecuting save test...\n");
  Graph* graph = CreateGraph(DEFAULT_HASH_SIZE);
  if (ImportGraph(DEFAULT_IMPORT_FILE_NAME, graph) != EXIT_SUCCESS) {
    printf("Error importing graph.");
    exit(EXIT_FAILURE);
  }

  // Start test
  start = clock();

  int res = SaveGraph(graph, DEFAULT_SAVE_FILE_NAME);

  // End test
  end = clock();

  // Error control
  switch (res) {
  case EXIT_SUCCESS:
    break;

  case ERROR_OPENING_FILE:
    printf("Error opening file.\n");
    exit(ERROR_OPENING_FILE);

  case ERROR_WRITING_HEADER:
    printf("Error writing header.\n");
    exit(ERROR_WRITING_HEADER);

  case ERROR_WRITING_VERTICES:
    printf("Error writing vertices\n");
    exit(ERROR_WRITING_VERTICES);

  case ERROR_WRITING_MARKER:
    printf("Error writing marker.\n");
    exit(ERROR_WRITING_MARKER);

  default:
    printf("Unknown Error.\n");
    break;
  }

  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Success. CPU time used during save: %f seconds\n", cpuTimeUsed);
  FreeGraph(graph);

#endif

#ifdef LOAD_TEST

  printf("\n\nExecuting load test...\n");

  // Start test
  start = clock();

  Graph* graph = LoadGraph(DEFAULT_LOAD_FILE_NAME);

  // End test
  end = clock();

  // Error control
  if (graph != NULL) {
    printf("Success.\n");
  }
  else {
    printf("Error.\n");
    exit(UNKNOWN_ERROR);
  }

  double cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used during load: %f seconds\n", cpuTimeUsed);
  FreeGraph(graph);

#endif

#ifdef FIND_ALL_PATHS_TEST

  printf("\n\nExecuting \"find all paths in a graph\" test...\n");

  Graph* graph = CreateGraph(FIND_ALL_PATHS_FILE_HASH_SIZE);
  int res = ImportGraph(DEFAULT_FIND_ALL_PATHS_FILE_NAME, graph);
  if (res != EXIT_SUCCESS) {
    printf("Error importing graph.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int numPaths = 0;
  PathNode* paths = FindAllPaths(graph, 2, 6, &numPaths);
  if (paths == NULL) {
    printf("Error finding all paths.\n");
    exit(EXIT_FAILURE);
  }

  PrintPaths(paths);

  FreeGraph(graph);

#endif

  return 0;
}
