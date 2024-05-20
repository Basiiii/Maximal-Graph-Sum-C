#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

typedef struct HeapNode {
  unsigned int vertex;
  unsigned int weight;
} HeapNode;

typedef struct MinHeap {
  HeapNode* nodes;
  unsigned int size;
  unsigned int capacity;
} MinHeap;

MinHeap* createMinHeap(unsigned int capacity);

void swapHeapNode(HeapNode* a, HeapNode* b);

void minHeapify(MinHeap* heap, int idx);

HeapNode extractMin(MinHeap* heap);

void insertMinHeap(MinHeap* heap, unsigned int vertex, unsigned int weight);

void DijkstraShortestPath(const Graph* graph, unsigned int src,
  unsigned int dest, unsigned int* minSum,
  unsigned int** path, unsigned int* pathLength);

void PrintShortestPath(unsigned int* path, unsigned int length,
  unsigned int minSum);

#endif  // !DIJKSTRA_H
