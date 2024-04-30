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

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
};

void Test();

#endif // !GRAPH_H


#include <stdio.h>
#include <stdlib.h>

// Struct to represent an edge
typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

// Struct to represent a vertex
typedef struct {
    Edge* head;
} Vertex;

// Struct to represent a graph
typedef struct {
    int numVertices;
    Vertex* array;
} Graph;
