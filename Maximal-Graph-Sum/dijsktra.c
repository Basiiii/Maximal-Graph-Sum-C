#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.h"
#include "vertices.h"

MaxHeap* createMaxHeap(unsigned int capacity) {
  MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
  heap->nodes = (HeapNode*)malloc(capacity * sizeof(HeapNode));
  heap->size = 0;
  heap->capacity = capacity;
  return heap;
}

void swapHeapNode(HeapNode* a, HeapNode* b) {
  HeapNode temp = *a;
  *a = *b;
  *b = temp;
}

void maxHeapify(MaxHeap* heap, int idx) {
  int largest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < heap->size &&
    heap->nodes[left].weight > heap->nodes[largest].weight) {
    largest = left;
  }
  if (right < heap->size &&
    heap->nodes[right].weight > heap->nodes[largest].weight) {
    largest = right;
  }
  if (largest != idx) {
    swapHeapNode(&heap->nodes[largest], &heap->nodes[idx]);
    maxHeapify(heap, largest);
  }
}

HeapNode extractMax(MaxHeap* heap) {
  if (heap->size == 0) {
    HeapNode emptyNode = { 0, 0 };
    return emptyNode;
  }

  HeapNode root = heap->nodes[0];
  heap->nodes[0] = heap->nodes[heap->size - 1];
  heap->size--;
  maxHeapify(heap, 0);

  return root;
}

void insertMaxHeap(MaxHeap* heap, unsigned int vertex, unsigned int weight) {
  if (heap->size == heap->capacity) {
    heap->capacity *= 2;
    heap->nodes =
      (HeapNode*)realloc(heap->nodes, heap->capacity * sizeof(HeapNode));
  }

  int i = heap->size++;
  heap->nodes[i].vertex = vertex;
  heap->nodes[i].weight = weight;

  while (i != 0 && heap->nodes[(i - 1) / 2].weight < heap->nodes[i].weight) {
    swapHeapNode(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void DijkstraMaxSum(const Graph* graph, unsigned int src, unsigned int dest,
  unsigned int* maxSum, unsigned int** path,
  unsigned int* pathLength) {
  unsigned int* dist =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));
  bool* visited = (bool*)malloc(graph->hashSize * sizeof(bool));
  unsigned int* prev =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));

  for (unsigned int i = 0; i < graph->hashSize; i++) {
    dist[i] = 0;
    visited[i] = false;
    prev[i] = UINT_MAX;
  }

  MaxHeap* maxHeap = createMaxHeap(graph->hashSize);
  insertMaxHeap(maxHeap, src, 0);
  dist[src] = 0;

  while (maxHeap->size > 0) {
    HeapNode maxNode = extractMax(maxHeap);
    unsigned int u = maxNode.vertex;

    if (visited[u]) {
      continue;
    }
    visited[u] = true;

    Vertex* vertex = FindVertex(graph, u);
    if (vertex) {
      Edge* edge = vertex->edges;
      while (edge != NULL) {
        unsigned int v = edge->dest;
        unsigned int weight = edge->weight;

        if (!visited[v] && dist[u] + weight > dist[v]) {
          dist[v] = dist[u] + weight;
          prev[v] = u;
          insertMaxHeap(maxHeap, v, dist[v]);
        }
        edge = edge->next;
      }
    }
  }

  *maxSum = dist[dest];

  // Reconstruct the path
  unsigned int count = 0;
  for (unsigned int v = dest; v != UINT_MAX; v = prev[v]) {
    count++;
  }

  *path = (unsigned int*)malloc(count * sizeof(unsigned int));
  unsigned int idx = count - 1;
  for (unsigned int v = dest; v != UINT_MAX; v = prev[v]) {
    (*path)[idx--] = v;
  }
  *pathLength = count;

  free(dist);
  free(visited);
  free(prev);
  free(maxHeap->nodes);
  free(maxHeap);
}

void PrintMaxSumPath(unsigned int* path, unsigned int length,
  unsigned int maxSum) {
  printf("Path with the highest sum (%u): ", maxSum);
  for (unsigned int i = 0; i < length; i++) {
    printf("%u", path[i]);
    if (i < length - 1) {
      printf(" -> ");
    }
  }
  printf("\n");
}
