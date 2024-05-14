/**

    @file      graph.h
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#ifndef GRAPH_H
#define GRAPH_H

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

#include <stdbool.h>
#include <stdlib.h>

#define MIN_LOAD_FACTOR 0.1
#define MAX_LOAD_FACTOR 0.5

#define DEFAULT_HASH_SIZE 100

typedef struct Edge {
  int dest;           // Destination vertex
  int weight;         // Weight of the edge
  struct Edge* next;  // Pointer to the next edge in the list
} Edge;

typedef struct Vertex {
  int vertex;   // Vertex index
  Edge* edges;  // List of adjacent vertices
} Vertex;

typedef struct Graph {
  int numVertices;
  int hashSize;
  Vertex** vertices;  // Hash table of vertices
} Graph;

// Hash function
int Hash(int vertexIndex, int hashSize);

// Function to create a new graph
Graph* CreateGraph(int numVertices, int hashSize);

// Function to create a new edge
Edge* CreateEdge(int dest, int weight);

// Function to add an edge to a vertex
void AddEdge(Vertex* vertex, int dest, int weight);

// Function to check if an edge already exists between two vertices
bool EdgeExists(Vertex* vertex, int dest);

// Function to check if a vertex already exists in the hash table
bool VertexExists(Graph* graph, int vertexIndex);

// Function to create a new vertex
Vertex* CreateVertex(int vertexIndex);

// Function to add a vertex to the graph
void AddVertex(Graph* graph, int vertexIndex);

void DisplayGraph(const Graph* graph);

bool EdgeExistsBetweenVertices(const Graph* graph, int src, int dest);

Vertex* FindVertex(const Graph* graph, int vertexIndex);

void RemoveEdge(Vertex* vertex, int dest);

void RemoveVertex(Graph* graph, int vertexIndex);

void DeleteGraph(Graph* graph);

#endif  // !GRAPH_H
