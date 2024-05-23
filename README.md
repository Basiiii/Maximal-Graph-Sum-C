# Maximal Graph Sum in C

This project implements a solution to a computationally challenging problem involving the calculation of the maximum possible summation of integers from a matrix of arbitrary dimensions. The solution utilizes advanced concepts from graph theory and programming to achieve the desired outcome.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [File Formats](#file-formats)
- [Algorithms](#algorithms)
- [Documentation](#documentation)

## Introduction

This repository contains the implementation of a graph structure and algorithms in C, developed as part of my Advanced Data Structures class at Instituto Politécnico do Cávado e do Ave. The focus is on implementing and manipulating graphs using advanced concepts in graph theory and programming in C.

The `generate-random-graph.py` file can be used to generate any sized graph in a CSV format to test the program.

## Features

- Graph structure using hash tables and linked lists for efficient memory usage and performance.
- Support for reading and writing graphs from/to CSV and binary files.
- Implemented algorithms include Dijkstra's algorithm for shortest path, Depth-First Search (DFS), and algorithms to find maximum paths.

## File Formats

### CSV Format

The CSV file format for graph input should follow this structure:

```csv
1;2;3;3;2
2;1;2;3;5
3;1;7
```

Where each line represents a vertex followed by its adjacent vertices and weights.

### Binary Format

The project supports reading and writing graphs in binary format. Use the provided functions to save and load graphs.

## Algorithms

### Depth-First Search (DFS)

The DFS algorithm is used to explore all vertices and edges of the graph to calculate the path with the maximum weight.

### Dijkstra's Algorithm

Dijkstra's algorithm is used to find the shortest path between vertices in a weighted graph.

### Maximum Longest Path

The algorithm to find the maximum path uses a modified version of Dijkstra's algorithm to compute the longest path between vertices.

## Documentation

All documentation for this project is available inside the `Docs` folder.
