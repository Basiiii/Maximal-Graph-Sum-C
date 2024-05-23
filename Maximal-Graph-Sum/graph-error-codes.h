/**
 *  @file      graph-error-codes.h
 *  @brief     Return code definitions which may appear from functions to the
 *             graph.
 *  @author    Enrique Rodrigues
 *  @date      22.05.2024
 *  @copyright © Enrique Rodrigues, 2024. All right reserved.
 */
#ifndef GRAPH_ERROR_CODES_H
#define GRAPH_ERROR_CODES_H

/* Generic return codes */
#define UNDEFINED_ERROR -1
#define INVALID_GRAPH -2

/* Edge return codes */
#define SUCCESS_REMOVING_EDGE 0
#define SUCCESS_REMOVING_EDGES 0
#define SUCCESS_REMOVING_OUTGOING_EDGES 0
#define SUCCESS_REMOVING_INCOMING_EDGES 0
#define EDGE_DOES_NOT_EXIST -3
#define ERROR_REMOVING_EDGE -5

/* Vertex return codes */
#define SUCCESS_ADDING_VERTEX 0
#define SUCCESS_REMOVING_VERTEX 0
#define INVALID_VERTEX -1
#define FAILURE_ADDING_VERTEX -4
#define VERTEX_EDGES_NULL -6
#define VERTEX_ALREADY_EXISTS -7
#define VERTEX_DOES_NOT_EXIST -8
#define FAILURE_CREATING_VERTEX -9

#endif  // !GRAPH_ERROR_CODES_H
