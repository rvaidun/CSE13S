#include "graph.h" // To be able to use Graph

#include "vertices.h"

#include <stdbool.h> // For Boolean
#include <stdint.h> // For uint32_t
#include <stdio.h> // For print
#include <stdlib.h> // For malloc and free
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// Constructor for the Graph ADT
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    if (g) {
        g->undirected = undirected;
        g->vertices = vertices;
        for (int i = 0; i < VERTICES; i++) {
            g->visited[i] = 0;
            for (int j = 0; j < VERTICES; j++) {
                g->matrix[i][j] = 0;
            }
        }
    }
    return g;
}

// Delets graph and frees up memory
void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
    }
    return;
}

// Returns total number of vertices in the graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// Adds an edge to the graph
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < G->vertices && j < G->vertices) { // Check to make sure no out of bounds
        G->matrix[i][j] = k;

        if (G->undirected) { // Add opposite if undirected
            G->matrix[j][i] = k;
        }
        return true;
    }
    return false;
}

// Says if there exists an edge from i to j
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices) {
        return G->matrix[i][j] > 0;
    }

    return false;
}

// Returns the weight of the edge from i to j
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices) {
        return G->matrix[i][j];
    }
    return 0;
}

// Says if a vertex has been visited yet
bool graph_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        return G->visited[v];
    }
    return false;
}

// Marks a vertex as visited
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }

    return;
}

// Marks a vertex as not visited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
    return;
}

// Debugger function to print out a graph
void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%d, ", G->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
