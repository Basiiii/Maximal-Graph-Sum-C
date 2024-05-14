/**

    @file      graph.c
    @brief
    @details   ~
    @author    Enrique George Rodrigues
    @date      29.04.2024
    @copyright © Enrique George Rodrigues, 2024. All right reserved.

**/
#include "graph.h"

#include <stdbool.h>
#include <stdio.h>

Graph* CreateGraph() {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (graph == NULL) {
    return NULL;
  }

  graph->numVertices = 0;
  graph->vertices = NULL;
  return graph;
}

void AddVertex(Graph* graph, int vertex) {
  if (VertexExists(graph, vertex)) {
    printf("Vertex %d already exists\n", vertex);
    return;
  }

  Vertex* newVertex = CreateVertex(vertex);
  if (newVertex == NULL) {
    return;
  }

  AddVertexToGraph(graph, newVertex);
}

bool VertexExists(Graph* graph, int vertex) {
  return FindVertex(graph, vertex) != NULL;
}

Edge* FindEdge(Vertex* vertex, int dest) {
  Edge* edge = vertex->edges;
  while (edge != NULL) {
    if (edge->dest == dest) {
      // Edge found
      return edge;
    }
    edge = edge->next;
  }
  // Edge not found
  return NULL;
}

bool EdgeExists(Vertex* vertex, int dest) {
  return FindEdge(vertex, dest) != NULL;
}

void AddEdgeIfNotExists(Graph* graph, int num1, int num2, int weight) {
  // Check if the edge already exists
  Vertex* vertex = FindVertex(graph, num1);
  if (vertex != NULL && !EdgeExists(vertex, num2)) {
    // Edge does not exist, add it
    AddEdge(graph, num1, num2, weight);
  }
}

Vertex* CreateVertex(int vertex) {
  Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
  if (newVertex == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }
  newVertex->vertex = vertex;
  newVertex->edges = NULL;
  newVertex->next = NULL;
  return newVertex;
}

void AddVertexToGraph(Graph* graph, Vertex* newVertex) {
  newVertex->next = graph->vertices;
  graph->vertices = newVertex;
  graph->numVertices++;
}

Vertex* FindSourceVertex(Graph* graph, int src) {
  return FindVertex(graph, src);
}

Edge* CreateEdge(int dest, int weight) {
  Edge* newEdge = (Edge*)malloc(sizeof(Edge));
  if (newEdge == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }
  newEdge->dest = dest;
  newEdge->weight = weight;
  newEdge->next = NULL;
  return newEdge;
}

void AddEdgeToSourceVertex(Vertex* sourceVertex, Edge* newEdge) {
  newEdge->next = sourceVertex->edges;
  sourceVertex->edges = newEdge;
}

void AddEdge(Graph* graph, int src, int dest, int weight) {
  Vertex* sourceVertex = FindSourceVertex(graph, src);
  if (sourceVertex == NULL) {
    printf("Source vertex %d not found\n", src);
    return;
  }

  Edge* newEdge = CreateEdge(dest, weight);
  if (newEdge == NULL) {
    return;
  }

  AddEdgeToSourceVertex(sourceVertex, newEdge);
}

void RemoveEdge(Graph* graph, int src, int dest) {
  Vertex* sourceVertex = FindVertex(graph, src);
  if (sourceVertex == NULL) {
    printf("Source vertex not found\n");
    return;
  }
  RemoveEdgeFromVertex(sourceVertex, dest);
}

void RemoveEdgeFromVertex(Vertex* vertex, int dest) {
  Edge* currentEdge = vertex->edges;
  Edge* prevEdge = NULL;

  while (currentEdge != NULL) {
    if (currentEdge->dest == dest) {
      if (prevEdge == NULL) {
        vertex->edges = currentEdge->next;
      } else {
        prevEdge->next = currentEdge->next;
      }
      free(currentEdge);
      return;
    }
    prevEdge = currentEdge;
    currentEdge = currentEdge->next;
  }
}

void RemoveEdgesToVertex(Graph* graph, int destVertex) {
  Vertex* currentVertex = graph->vertices;
  while (currentVertex != NULL) {
    if (currentVertex->vertex != destVertex) {
      RemoveEdgeFromVertex(currentVertex, destVertex);
    }
    currentVertex = currentVertex->next;
  }
}

void RemoveVertex(Graph* graph, int vertexToRemove) {
  Vertex* prevVertex = NULL;
  Vertex* currentVertex = graph->vertices;

  while (currentVertex != NULL && currentVertex->vertex != vertexToRemove) {
    prevVertex = currentVertex;
    currentVertex = currentVertex->next;
  }

  if (currentVertex != NULL) {
    Edge* currentEdge = currentVertex->edges;
    while (currentEdge != NULL) {
      Edge* nextEdge =
          currentEdge->next;  // Store next edge before removing current edge
      RemoveEdge(graph, currentVertex->vertex, currentEdge->dest);
      currentEdge = nextEdge;
    }

    if (prevVertex == NULL) {
      graph->vertices = currentVertex->next;
    } else {
      prevVertex->next = currentVertex->next;
    }
    free(currentVertex);
    graph->numVertices--;
  } else {
    printf("Vertex %d not found\n", vertexToRemove);
  }
}

void DisplayGraph(Graph* graph) {
  printf("Graph:\n");
  Vertex* vertex = graph->vertices;
  while (vertex != NULL) {
    printf("Vertex %d -> ", vertex->vertex);
    Edge* edge = vertex->edges;
    while (edge != NULL) {
      printf("(%d, %d) ", edge->dest, edge->weight);
      edge = edge->next;
    }
    printf("\n");
    vertex = vertex->next;
  }
}

Vertex* FindVertex(Graph* graph, int vertex) {
  Vertex* currentVertex = graph->vertices;
  while (currentVertex != NULL) {
    if (currentVertex->vertex == vertex) {
      return currentVertex;
    }
    currentVertex = currentVertex->next;
  }
  return NULL;
}

void FreeGraph(Graph* graph) {
  if (graph == NULL) {
    return;
  }

  Vertex* currentVertex = graph->vertices;
  while (currentVertex != NULL) {
    Vertex* nextVertex = currentVertex->next;
    Edge* currentEdge = currentVertex->edges;
    while (currentEdge != NULL) {
      Edge* nextEdge = currentEdge->next;
      free(currentEdge);
      currentEdge = nextEdge;
    }
    free(currentVertex);
    currentVertex = nextVertex;
  }

  free(graph);
}

void AddVertexIfNotExists(Graph* graph, int vertexIndex) {
  if (FindVertex(graph, vertexIndex) == NULL) {
    AddVertex(graph, vertexIndex);
  }
}
