#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

typedef struct HeapNode {
  unsigned int vertex;
  unsigned int weight;
} HeapNode;

typedef struct MaxHeap {
  HeapNode* nodes;
  unsigned int size;
  unsigned int capacity;
} MaxHeap;

MaxHeap* createMaxHeap(unsigned int capacity);

void swapHeapNode(HeapNode* a, HeapNode* b);

void maxHeapify(MaxHeap* heap, int idx);

HeapNode extractMax(MaxHeap* heap);

void insertMaxHeap(MaxHeap* heap, unsigned int vertex, unsigned int weight);

void DijkstraMaxSum(const Graph* graph, unsigned int src, unsigned int dest,
  unsigned int* maxSum, unsigned int** path,
  unsigned int* pathLength);

void PrintMaxSumPath(unsigned int* path, unsigned int length,
  unsigned int maxSum);

#endif  // !DIJKSTRA_H
