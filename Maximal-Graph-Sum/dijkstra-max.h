/**

    @file      dijkstra-max.h
    @brief     Function definitions for finding the path with maximum weight in
               a graph.
    @author    Enrique George Rodrigues
    @date      23.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#ifndef DIJKSTRA_MAX_H
#define DIJKSTRA_MAX_H

#include "dijkstra-structure.h"
#include "graph.h"

/**
    @brief Creates a new MaxHeap with the specified capacity.
    @param capacity The initial capacity of the MaxHeap.
    @return A pointer to the newly created MaxHeap, or NULL if memory allocation
            fails.
**/
MaxHeap* CreateMaxHeap(unsigned int capacity);

/**
    @brief Swaps two HeapNode elements.

    @param a Pointer to the first HeapNode.
    @param b Pointer to the second HeapNode.
**/
void SwapHeapNodeMaxHeap(HeapNode* a, HeapNode* b);

/**
    @brief Maintains heap property for a given node.

    @param heap Pointer to the MaxHeap.
    @param idx Index of the node to start heapifying from.
**/
void MaxHeapify(MaxHeap* heap, int idx);

/**
    @brief Extracts the maximum node (root) from the MaxHeap.

    @param heap Pointer to the MaxHeap.

    @return The maximum HeapNode extracted from the heap.
**/
HeapNode ExtractMax(MaxHeap* heap);

/**
    @brief Ensures the capacity of the MaxHeap.

    @param heap Pointer to the MaxHeap.
**/
void EnsureCapacityMaxHeap(MaxHeap* heap);

/**
    @brief Inserts a new node into the MaxHeap.

    @param heap Pointer to the MaxHeap.
    @param vertex Vertex index to insert.
    @param weight Weight associated with the vertex.

    @note If the heap is full, it will be resized to accommodate more elements.
**/
void InsertNodeMaxHeap(MaxHeap* heap, unsigned int vertex, unsigned int weight);

/**
    @brief Finds the path with maximum weight in a graph using a modified
           Dijkstra's algorithm.
    @param graph Pointer to the graph structure.
    @param src Source vertex index.
    @param dest Destination vertex index.
    @param maxWeight Pointer to store the maximum path weight.
    @param path Pointer to store the path vertices with maximum weight.
    @param pathLength Pointer to store the length of the path.
**/
void DijkstraMaxPath(const Graph* graph, unsigned int src, unsigned int dest,
  unsigned int* maxWeight, unsigned int** path,
  unsigned int* pathLength);

/**
    @brief Prints the path found by the DijkstraMaxPath function.

    @param path Array of vertices representing the path.
    @param length Number of vertices in the path.
    @param maxWeight Maximum weight associated with the path.
**/
void PrintLongestPath(const unsigned int* path, unsigned int length,
  unsigned int maxWeight);

#endif  // !DIJKSTRA_MAX_H
