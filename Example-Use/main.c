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

#include "dijkstra-max.h"
#include "dijkstra-min.h"
#include "edges.h"
#include "export-graph.h"
#include "graph.h"
#include "import-graph.h"
#include "search.h"
#include "vertices.h"

/* ============================= */
/* Define Default file locations */
/* ============================= */
#define USE_DESKTOP  // Define this if you have the files on your Desktop
#ifdef USE_DESKTOP
#define DEFAULT_USERS_FILE "C:\\Users\\"
#define WINDOWS_USER_NAME "user\\"
#define DEFAULT_USER_DIR DEFAULT_USERS_FILE WINDOWS_USER_NAME
#define DEFAULT_LOCATION DEFAULT_USER_DIR "Desktop\\"
#else
#define DEFAULT_LOCATION ""
#endif

#define DEFAULT_IMPORT_FILE_NAME DEFAULT_LOCATION "1000.txt"
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

/* ========================== */
/*            Misc            */
/* ========================== */
#define UNKNOWN_ERROR -100
#define DIJKSTRA_SOURCE_VERTEX 5
#define DIJKSTRA_DESTINATION_VERTEX 12

/* =================================== */
/* Define the test you wish to execute */
/* =================================== */
#define CREATE_ADD_VERTICES_TEST
#define CREATE_ADD_EDGES_TEST
#define IMPORT_TEST
#define EXPORT_TEST
#define SAVE_TEST
#define LOAD_TEST
#define FIND_ALL_PATHS_TEST
#define DIJKSTRA_SHORTEST_PATH
#define DIJKSTRA_LONGEST_PATH

/* =================== */
/* Include the library */
/* =================== */
#pragma comment(lib, "Maximal-Graph-Sum.lib")

int main() {
  // Variables used to measure time
  clock_t start = 0.0;
  clock_t end = 0.0;
  double cpuTimeUsed = 0.0;

#ifdef CREATE_ADD_VERTICES_TEST

  printf("\n\nExecuting Create Add Vertices test...\n");

  Graph* graphVerticesTest = CreateGraph(ONE_MILLION_TEST_HASH_SIZE);

  printf("Starting number of vertices: %u\n", graphVerticesTest->numVertices);
  start = clock();

  // Create and add one million vertices
  for (unsigned int i = 0; i < ONE_MILLION_TEST_NUM_VERTICES; i++) {
    CreateAddVertex(graphVerticesTest, i);
  }

  end = clock();
  printf("Ending number of vertices: %u\n", graphVerticesTest->numVertices);

  // Free Graph from memory
  FreeGraph(graphVerticesTest);

  // Calculate the CPU time used
  cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used: %f seconds\n", cpuTimeUsed);

#endif  //  CREATE_ADD_VERTICES_TEST

#ifdef CREATE_ADD_EDGES_TEST

  printf("\n\nExecuting Create Add Edges test...\n");

  Graph* graphEdgesTest = CreateGraph(ONE_MILLION_TEST_HASH_SIZE);

  // Add vertices to the graph
  for (unsigned int i = 0; i < ONE_MILLION_TEST_NUM_VERTICES; i++) {
    if (CreateAddVertex(graphEdgesTest, i) != EXIT_SUCCESS) {
      printf("Error creating vertex for testing.\n");
      FreeGraph(graphEdgesTest);
      return 1;
    }
  }

  // Choose a specific vertex to add edges to
  unsigned int srcVertexId = 0;
  Vertex* srcVertex = FindVertex(graphEdgesTest, srcVertexId);
  if (srcVertex == NULL) {
    printf("Source vertex not found in the graph.\n");
    FreeGraph(graphEdgesTest);
    return 1;
  }

  // Begin Test
  printf("Vertices ready, beginning test.\n");
  start = clock();

  // Create and add edges to the specified vertex
  for (unsigned int i = 0; i < ONE_MILLION_TEST_NUM_EDGES; i++) {
    Edge* edge = CreateEdge(i, 1);
    AddEdgeToVertex(srcVertex, edge);
  }

  // End test
  end = clock();
  cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
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
  FreeGraph(graphEdgesTest);

#endif  // CREATE_ADD_EDGE_TEST

#ifdef IMPORT_TEST

  printf("\n\nExecuting import test...\n");
  Graph* graphImportTest = CreateGraph(DEFAULT_HASH_SIZE);

  // Start test
  start = clock();

  int resImport = ImportGraph(DEFAULT_IMPORT_FILE_NAME, graphImportTest);

  // End test
  end = clock();

  // Error control
  if (resImport == EXIT_SUCCESS) {
    printf("Success.\n");
  }
  else {
    switch (resImport) {
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

  cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used during import: %f seconds\n", cpuTimeUsed);
  FreeGraph(graphImportTest);

#endif

#ifdef EXPORT_TEST

  printf("\n\nExecuting export test...\n");
  Graph* graphExportTest = CreateGraph(DEFAULT_HASH_SIZE);
  if (ImportGraph(DEFAULT_IMPORT_FILE_NAME, graphExportTest) != EXIT_SUCCESS) {
    printf("Error importing graph.");
    exit(EXIT_FAILURE);
  }

  // Start test
  start = clock();

  int resExport = ExportGraph(DEFAULT_EXPORT_FILE_NAME, graphExportTest);

  // End test
  end = clock();

  // Error control
  if (resExport == EXIT_SUCCESS) {
    printf("Success.\n");
  }
  else {
    printf("Error creating file.\n");
    FreeGraph(graphExportTest);
    exit(EXIT_FAILURE);
  }

  cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used during export: %f seconds\n", cpuTimeUsed);
  FreeGraph(graphExportTest);

#endif

#ifdef SAVE_TEST

  printf("\n\nExecuting save test...\n");
  Graph* graphSaveTest = CreateGraph(DEFAULT_HASH_SIZE);
  if (ImportGraph(DEFAULT_IMPORT_FILE_NAME, graphSaveTest) != EXIT_SUCCESS) {
    printf("Error importing graph.");
    exit(EXIT_FAILURE);
  }

  // Start test
  start = clock();

  int resSave = SaveGraph(graphSaveTest, DEFAULT_SAVE_FILE_NAME);

  // End test
  end = clock();

  // Error control
  switch (resSave) {
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

  cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Success. CPU time used during save: %f seconds\n", cpuTimeUsed);
  FreeGraph(graphSaveTest);

#endif

#ifdef LOAD_TEST

  printf("\n\nExecuting load test...\n");

  // Start test
  start = clock();

  Graph* graphLoadTest = LoadGraph(DEFAULT_LOAD_FILE_NAME);

  // End test
  end = clock();

  // Error control
  if (graphLoadTest != NULL) {
    printf("Success.\n");
  }
  else {
    printf("Error.\n");
    exit(UNKNOWN_ERROR);
  }

  cpuTimeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("CPU time used during load: %f seconds\n", cpuTimeUsed);
  FreeGraph(graphLoadTest);

#endif

#ifdef FIND_ALL_PATHS_TEST

  printf("\n\nExecuting \"find all paths in a graph\" test...\n");

  Graph* graphFAP = CreateGraph(FIND_ALL_PATHS_FILE_HASH_SIZE);
  int importPrepareRes =
    ImportGraph(DEFAULT_FIND_ALL_PATHS_FILE_NAME, graphFAP);
  if (importPrepareRes != EXIT_SUCCESS) {
    printf("Error importing graph.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int numPaths = 0;
  PathNode* paths = FindAllPaths(graphFAP, 2, 6, &numPaths);
  if (paths == NULL) {
    printf("Error finding all paths.\n");
    exit(EXIT_FAILURE);
  }

  PrintPaths(paths);

  FreeGraph(graphFAP);

#endif

#ifdef DIJKSTRA_SHORTEST_PATH

  printf("\n\nExecuting Dijkstra shortest path test from 5 to 12...\n");

  Graph* graphDijkstra = CreateGraph(FIND_ALL_PATHS_FILE_HASH_SIZE);
  int importDijkstraRes =
    ImportGraph(DEFAULT_FIND_ALL_PATHS_FILE_NAME, graphDijkstra);
  if (importDijkstraRes != EXIT_SUCCESS) {
    printf("Error importing graph.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int srcDijkstra = DIJKSTRA_SOURCE_VERTEX;
  unsigned int destDijkstra = DIJKSTRA_DESTINATION_VERTEX;

  unsigned int minSumDijkstra;      // Minimum sum of weights
  unsigned int* pathDijkstra;       // Array to store the path
  unsigned int pathLengthDijkstra;  // Length of the path

  // Run Dijkstra's algorithm
  DijkstraMinPath(graphDijkstra, srcDijkstra, destDijkstra, &minSumDijkstra,
    &pathDijkstra, &pathLengthDijkstra);

  // Print the shortest path and its total weight
  PrintShortestPath(pathDijkstra, pathLengthDijkstra, minSumDijkstra);

  // Free allocated memory
  free(pathDijkstra);
  FreeGraph(graphDijkstra);

#endif

#ifdef DIJKSTRA_LONGEST_PATH

  printf("\n\nExecuting Dijkstra longest path test from 5 to 12...\n");

  Graph* graphDijkstra2 = CreateGraph(FIND_ALL_PATHS_FILE_HASH_SIZE);
  int importDijkstraRes2 =
    ImportGraph(DEFAULT_FIND_ALL_PATHS_FILE_NAME, graphDijkstra2);
  if (importDijkstraRes2 != EXIT_SUCCESS) {
    printf("Error importing graph.\n");
    exit(EXIT_FAILURE);
  }

  unsigned int maxWeight;
  unsigned int* path;
  unsigned int pathLength;
  unsigned int src = DIJKSTRA_SOURCE_VERTEX;
  unsigned int dest = DIJKSTRA_DESTINATION_VERTEX;

  // Calculate the longest path
  DijkstraMaxPath(graphDijkstra2, src, dest, &maxWeight, &path, &pathLength);

  // Print the longest path
  PrintLongestPath(path, pathLength, maxWeight);

  // Clean up allocated memory
  free(path);
  FreeGraph(graphDijkstra2);

#endif

  return 0;
}
