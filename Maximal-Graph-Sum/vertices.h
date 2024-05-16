#pragma once
#include "graph.h"

#define VERTEX_ALREADY_EXISTS -1
#define FAILURE_CREATE_VERTEX -2

// Hash function
int Hash(int vertexIndex, int hashSize);

// Function to check if a vertex already exists in the hash table
bool VertexExists(Graph* graph, int vertexIndex);

Vertex* FindVertex(const Graph* graph, int vertexIndex);

// Function to create a new vertex
Vertex* CreateVertex(int vertexIndex);

// Function to add a vertex to the graph
void AddVertex(Graph* graph, int vertexIndex);

void RemoveVertex(Graph* graph, int vertexIndex);
