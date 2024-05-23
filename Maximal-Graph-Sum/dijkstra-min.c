/**

    @file      dijkstra-min.c
    @brief     Function implementations of Dijkstra algorithm to find shortest
               path.
    @author    Enrique George Rodrigues
    @date      23.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include "dijkstra-min.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra-structure.h"
#include "vertices.h"

/**
    @brief Creates a new MinHeap with the specified capacity.
    @param capacity The initial capacity of the MinHeap.
    @return A pointer to the newly created MinHeap, or NULL if memory allocation
            fails.
**/
MinHeap* CreateMinHeap(unsigned int capacity) {
  MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
  if (heap == NULL) {
    return NULL;
  }

  heap->nodes = (HeapNode*)malloc(capacity * sizeof(HeapNode));
  if (heap->nodes == NULL) {
    free(heap);
    return NULL;
  }

  heap->size = 0;
  heap->capacity = capacity;
  return heap;
}

/**
    @brief Swaps two HeapNode elements.

    @param a Pointer to the first HeapNode.
    @param b Pointer to the second HeapNode.
**/
void SwapHeapNode(HeapNode* a, HeapNode* b) {
  HeapNode temp = *a;
  *a = *b;
  *b = temp;
}

/**
    @brief Maintains heap property for a given node.

    @param heap Pointer to the MinHeap.
    @param idx Index of the node to start heapifying from.
**/
void MinHeapify(MinHeap* heap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < heap->size &&
    heap->nodes[left].weight < heap->nodes[smallest].weight) {
    smallest = left;
  }
  if (right < heap->size &&
    heap->nodes[right].weight < heap->nodes[smallest].weight) {
    smallest = right;
  }
  if (smallest != idx) {
    SwapHeapNode(&heap->nodes[smallest], &heap->nodes[idx]);
    MinHeapify(heap, smallest);
  }
}

/**
    @brief Extracts the minimum node (root) from the MinHeap.

    @param heap Pointer to the MinHeap.

    @return The minimum HeapNode extracted from the heap.
**/
HeapNode ExtractMin(MinHeap* heap) {
  if (heap->size == 0) {
    HeapNode emptyNode = { 0, UINT_MAX };
    return emptyNode;
  }

  HeapNode root = heap->nodes[0];
  heap->nodes[0] = heap->nodes[heap->size - 1];
  heap->size--;
  MinHeapify(heap, 0);

  return root;
}

/**
    @brief Ensures the capacity of the MinHeap.

    @param heap Pointer to the MinHeap.
**/
void EnsureCapacity(MinHeap* heap) {
  if (heap->size == heap->capacity) {
    heap->capacity *= 2;
    HeapNode* new_nodes =
      (HeapNode*)realloc(heap->nodes, heap->capacity * sizeof(HeapNode));
    if (new_nodes == NULL) {
      exit(EXIT_FAILURE);
    }
    heap->nodes = new_nodes;
  }
}

/**
    @brief Inserts a new node into the MinHeap.

    @param heap Pointer to the MinHeap.
    @param vertex Vertex index to insert.
    @param weight Weight associated with the vertex.

    @note If the heap is full, it will be resized to accommodate more elements.
**/
void InsertNode(MinHeap* heap, unsigned int vertex, unsigned int weight) {
  EnsureCapacity(heap);

  int i = heap->size;
  heap->size++;

  heap->nodes[i].vertex = vertex;
  heap->nodes[i].weight = weight;

  // Perform heapify-up
  while (i != 0 && heap->nodes[(i - 1) / 2].weight > heap->nodes[i].weight) {
    SwapHeapNode(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

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
  unsigned int* pathLength) {
  unsigned int* dist =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));
  if (dist == NULL) {
    exit(EXIT_FAILURE);
  }
  bool* visited = (bool*)malloc(graph->hashSize * sizeof(bool));
  if (visited == NULL) {
    exit(EXIT_FAILURE);
  }

  unsigned int* prev =
    (unsigned int*)malloc(graph->hashSize * sizeof(unsigned int));
  if (prev == NULL) {
    exit(EXIT_FAILURE);
  }

  for (unsigned int i = 0; i < graph->hashSize; i++) {
    dist[i] = UINT_MAX;
    visited[i] = false;
    prev[i] = UINT_MAX;
  }

  MinHeap* minHeap = CreateMinHeap(graph->hashSize);
  if (minHeap == NULL) {
    exit(EXIT_FAILURE);
  }

  InsertNode(minHeap, src, 0);
  dist[src] = 0;

  while (minHeap->size > 0) {
    HeapNode minNode = ExtractMin(minHeap);
    unsigned int u = minNode.vertex;

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

        if (!visited[v] && dist[u] != UINT_MAX && dist[u] + weight < dist[v]) {
          dist[v] = dist[u] + weight;
          prev[v] = u;
          InsertNode(minHeap, v, dist[v]);
        }
        edge = edge->next;
      }
    }
  }

  *minSum = dist[dest];

  // Reconstruct the path
  unsigned int count = 0;
  for (unsigned int v = dest; v != UINT_MAX; v = prev[v]) {
    count++;
  }

  *path = (unsigned int*)malloc(count * sizeof(unsigned int));
  if (path == NULL) {
    exit(EXIT_FAILURE);
  }

  unsigned int idx = count - 1;
  for (unsigned int v = dest; v != UINT_MAX; v = prev[v]) {
    (*path)[idx--] = v;
  }
  *pathLength = count;

  free(dist);
  free(visited);
  free(prev);
  free(minHeap->nodes);
  free(minHeap);
}

/**
    @brief Prints the shortest path found by Dijkstra's algorithm.

    @param path Array of vertices representing the shortest path.
    @param length Number of vertices in the shortest path.
    @param minSum Minimum path sum associated with the shortest path.
**/
void PrintShortestPath(const unsigned int* path, unsigned int length,
  unsigned int minSum) {
  printf("Path with the lowest sum (%u): ", minSum);
  for (unsigned int i = 0; i < length; i++) {
    printf("%u", path[i]);
    if (i < length - 1) {
      printf(" -> ");
    }
  }
  printf("\n");
}
