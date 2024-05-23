/**

    @file      dijkstra-min.h
    @brief     Function definitions for Dijkstra algorithm to find the shortest
               path.
    @author    Enrique George Rodrigues
    @date      23.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#ifndef DIJKSTRA_MIN_H
#define DIJKSTRA_MIN_H

#include "dijkstra-structure.h"
#include "graph.h"

/**
    @brief Creates a new MinHeap with the specified capacity.
    @param capacity The initial capacity of the MinHeap.
    @return A pointer to the newly created MinHeap, or NULL if memory allocation
            fails.
**/
MinHeap* CreateMinHeap(unsigned int capacity);

/**
    @brief Swaps two HeapNode elements.

    @param a Pointer to the first HeapNode.
    @param b Pointer to the second HeapNode.
**/
void SwapHeapNode(HeapNode* a, HeapNode* b);

/**
    @brief Maintains heap property for a given node.

    @param heap Pointer to the MinHeap.
    @param idx Index of the node to start heapifying from.
**/
void MinHeapify(MinHeap* heap, int idx);

/**
    @brief Extracts the minimum node (root) from the MinHeap.

    @param heap Pointer to the MinHeap.

    @return The minimum HeapNode extracted from the heap.
**/
HeapNode ExtractMin(MinHeap* heap);

/**
    @brief Ensures the capacity of the MinHeap.

    @param heap Pointer to the MinHeap.
**/
void EnsureCapacity(MinHeap* heap);

/**
    @brief Inserts a new node into the MinHeap.

    @param heap Pointer to the MinHeap.
    @param vertex Vertex index to insert.
    @param weight Weight associated with the vertex.

    @note If the heap is full, it will be resized to accommodate more elements.
**/
void InsertNode(MinHeap* heap, unsigned int vertex, unsigned int weight);

/**
    @brief Computes the shortest path in a graph using Dijkstra's algorithm.
    @param graph Pointer to the graph structure.
    @param src Source vertex index.
    @param dest Destination vertex index.
    @param minSum Pointer to store the minimum path sum.
    @param path Pointer to store the shortest path vertices.
    @param pathLength Pointer to store the length of the shortest path.
**/
void DijkstraMinPath(const Graph* graph, unsigned int src, unsigned int dest,
  unsigned int* minSum, unsigned int** path,
  unsigned int* pathLength);

/**
    @brief Prints the shortest path found by Dijkstra's algorithm.

    @param path Array of vertices representing the shortest path.
    @param length Number of vertices in the shortest path.
    @param minSum Minimum path sum associated with the shortest path.
**/
void PrintShortestPath(const unsigned int* path, unsigned int length,
  unsigned int minSum);

#endif  // !DIJKSTRA_MIN_H
