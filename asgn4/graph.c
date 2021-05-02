#include "graph.h" // To be able to use Graph

#include "vertices.h"

#include <stdbool.h> // For Boolean
#include <stdint.h> // For uint32_t
#include <stdio.h> // For print
#include <stdlib.h> // For malloc and free
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool *visited;
    uint32_t **matrix;
};

// Constructor for the Graph ADT
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    if (g) {
        g->undirected = undirected;
        g->vertices = vertices;
        g->visited = (bool *) calloc(VERTICES, sizeof(bool));
	g->matrix = calloc(VERTICES, sizeof(uint32_t*));
	for(int i = 0; i < VERTICES; i++) {
		g->matrix[i] = (uint32_t *) calloc(VERTICES,sizeof(uint32_t));
	}
    }
    return g;
}

void graph_delete(Graph **G) {
    if (*G) {
        free((*G)->visited);
	for(int i = 0; i < VERTICES; i++) {
		free((*G)->matrix[i]);
	}
	free((*G)->matrix);
        free(*G);
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < G->vertices && j < G->vertices) {
        G->matrix[i][j] = k;

        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return true;
    }
    return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices) {
        return G->matrix[i][j] > 0;
    }

    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices) {
        return G->matrix[i][j];
    }
    return 0;
}

bool graph_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        return G->visited[v];
    }
    return false;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }

    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
    return;
}

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
