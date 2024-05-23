/**

    @file      dijkstra-structure.h
    @brief     Structure definitions for Dijkstra algorithm.
    @author    Enrique George Rodrigues
    @date      23.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#ifndef DIJKSTRA_STRUCTURE_H
#define DIJKSTRA_STRUCTURE_H

/**
    @struct HeapNode
    @brief  Represents a node in the heap used for Dijkstra's algorithm.
**/
typedef struct HeapNode {
  unsigned int vertex;  // vertex index
  unsigned int weight;  // vertex weight
} HeapNode;

/**
    @struct MinHeap
    @brief Min-heap data structure for Dijkstra's algorithm.
**/
typedef struct MinHeap {
  HeapNode* nodes;        // Array of HeapNode elements
  unsigned int size;      // Number of elements in the heap
  unsigned int capacity;  // Maximum capacity of heap
} MinHeap;

/**
    @struct MaxHeap
    @brief Max-heap data structure for finding the path with maximum weight.
**/
typedef struct MaxHeap {
  HeapNode* nodes;        // Array of heap nodes
  unsigned int size;      // Current number of elements in heap
  unsigned int capacity;  // Capacity of heap
} MaxHeap;

#endif  // !DIJKSTRA_STRUCTURE_H
