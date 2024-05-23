/**

    @file      dijkstra-max.c
    @brief     Function implementations of finding the path with maximum weight
               in a graph using Dijkstra's algorithm with a max-heap approach.
    @author    Enrique George Rodrigues
    @date      23.05.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include "dijkstra-max.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra-structure.h"
#include "vertices.h"

/**
    @brief Creates a new MaxHeap with the specified capacity.
    @param capacity The initial capacity of the MaxHeap.
    @return A pointer to the newly created MaxHeap, or NULL if memory allocation
            fails.
**/
MaxHeap* CreateMaxHeap(unsigned int capacity) {
  MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
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
void SwapHeapNodeMaxHeap(HeapNode* a, HeapNode* b) {
  HeapNode temp = *a;
  *a = *b;
  *b = temp;
}

/**
    @brief Maintains heap property for a given node.

    @param heap Pointer to the MaxHeap.
    @param idx Index of the node to start heapifying from.
**/
void MaxHeapify(MaxHeap* heap, int idx) {
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
    SwapHeapNodeMaxHeap(&heap->nodes[idx], &heap->nodes[largest]);
    MaxHeapify(heap, largest);
  }
}

/**
    @brief Extracts the maximum node (root) from the MaxHeap.

    @param heap Pointer to the MaxHeap.

    @return The maximum HeapNode extracted from the heap.
**/
HeapNode ExtractMax(MaxHeap* heap) {
  if (heap->size == 0) {
    HeapNode emptyNode = { 0, 0 };
    return emptyNode;
  }

  HeapNode root = heap->nodes[0];
  heap->nodes[0] = heap->nodes[heap->size - 1];
  heap->size--;
  MaxHeapify(heap, 0);

  return root;
}

/**
    @brief Ensures the capacity of the MaxHeap.

    @param heap Pointer to the MaxHeap.
**/
void EnsureCapacityMaxHeap(MaxHeap* heap) {
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
    @brief Inserts a new node into the MaxHeap.

    @param heap Pointer to the MaxHeap.
    @param vertex Vertex index to insert.
    @param weight Weight associated with the vertex.

    @note If the heap is full, it will be resized to accommodate more elements.
**/
void InsertNodeMaxHeap(MaxHeap* heap, unsigned int vertex,
  unsigned int weight) {
  EnsureCapacityMaxHeap(heap);

  int i = heap->size;
  heap->size++;

  heap->nodes[i].vertex = vertex;
  heap->nodes[i].weight = weight;

  // Perform heapify-up
  while (i != 0 && heap->nodes[(i - 1) / 2].weight < heap->nodes[i].weight) {
    SwapHeapNodeMaxHeap(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

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
    dist[i] = 0;  // Start with 0 distance
    visited[i] = false;
    prev[i] = UINT_MAX;
  }

  MaxHeap* maxHeap = CreateMaxHeap(graph->hashSize);
  if (maxHeap == NULL) {
    exit(EXIT_FAILURE);
  }

  InsertNodeMaxHeap(maxHeap, src, 0);
  dist[src] = 0;

  while (maxHeap->size > 0) {
    HeapNode maxNode = ExtractMax(maxHeap);
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
          InsertNodeMaxHeap(maxHeap, v, dist[v]);
        }
        edge = edge->next;
      }
    }
  }

  *maxWeight = dist[dest];

  // Reconstruct the path
  unsigned int count = 0;
  for (unsigned int v = dest; v != UINT_MAX; v = prev[v]) {
    count++;
  }

  *path = (unsigned int*)malloc(count * sizeof(unsigned int));
  if (*path == NULL) {
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
  free(maxHeap->nodes);
  free(maxHeap);
}

/**
    @brief Prints the path found by the DijkstraMaxPath function.

    @param path Array of vertices representing the path.
    @param length Number of vertices in the path.
    @param maxWeight Maximum weight associated with the path.
**/
void PrintLongestPath(const unsigned int* path, unsigned int length,
  unsigned int maxWeight) {
  printf("Path with the maximum weight (%u): ", maxWeight);
  for (unsigned int i = 0; i < length; i++) {
    printf("%u", path[i]);
    if (i < length - 1) {
      printf(" -> ");
    }
  }
  printf("\n");
}
