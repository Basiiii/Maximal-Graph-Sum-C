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

typedef struct Edge {
  int dest;           // Destination vertex
  int weight;         // Weight of the edge
  struct Edge* next;  // Pointer to the next edge in the list
} Edge;

typedef struct Vertex {
  int vertex;           // Vertex index
  Edge* edges;          // List of adjacent vertices
  struct Vertex* next;  // Pointer to the next vertex in the list
} Vertex;

typedef struct Graph {
  int numVertices;
  Vertex* vertices;  // Linked list of vertices
} Graph;

Graph* CreateGraph();

// misc helper funcs
Vertex* FindVertex(Graph* graph, int vertex);
Edge* FindEdge(Vertex* vertex, int dest);
bool VertexExists(Graph* graph, int vertex);
bool VertexExists(Graph* graph, int vertex);
void AddVertexIfNotExists(Graph* graph, int vertexIndex);
void AddEdgeIfNotExists(Graph* graph, int num1, int num2, int weight);
Vertex* FindSourceVertex(Graph* graph, int src);

// Create Add Vertices (nodes)
Vertex* CreateVertex(int vertex);
void AddVertexToGraph(Graph* graph, Vertex* newVertex);
void AddVertex(Graph* graph, int vertex);

// Create Add Edges
Edge* CreateEdge(int dest, int weight);
void AddEdgeToSourceVertex(Vertex* sourceVertex, Edge* newEdge);
void AddEdge(Graph* graph, int src, int dest, int weight);

// Remove Edges
void RemoveEdge(Graph* graph, int src, int dest);
void RemoveEdgeFromVertex(Vertex* vertex, int dest);
void RemoveEdgesToVertex(Graph* graph, int destVertex);

// Remove Vertex (node)
void RemoveVertex(Graph* graph, int vertexToRemove);

// Display
void DisplayGraph(Graph* graph);

// Free
void FreeGraph(Graph* graph);

#endif  // !GRAPH_H
