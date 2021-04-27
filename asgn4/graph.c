#include "vertices.h"
#include <stdbool.h> // For Boolean
#include <stdint.h> // For uint32_t
#include <stdio.h> // For print
#include "graph.h" // To be able to use Graph
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
    }
    return g;
}

void graph_delete(Graph **G) {
    if (*G) {
        free(*G);
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i > G->vertices || j > G->vertices) {
	return false;
    }
    G->matrix[i][j] = k;

    if (G->undirected) {
	G->matrix[j][i] = k;
    }

    return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i > G->vertices || j > G->vertices) {
	return false;
    }

    return G->matrix[i][j] > 0;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i > G->vertices || j > G->vertices) {
	return 0;
    }

    return G->matrix[i][j];
}

bool graph_visited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
	return false;
    }

    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
	return;
    }

    G->visited[v] = true;
    return;
}


void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
	return;
    }

    G->visited[v] = false;
    return;
}

void graph_print(Graph *G) {

    printf("Vertices: %d\n", G->vertices);

    printf("Visited: \n");
    for (int i = 0; i < G->vertices; i++) {
	printf("%d, ", G->visited[i]);
    }
    printf("\n");

    printf("Matrix: \n");
    for (int i = 0; i < G->vertices; i++) {
	for (int j = 0; j < G->vertices; j++) {
	    printf("%d, ", G->matrix[i][j]);
	}
	printf("\n");
    }
    printf("\n");
    return;
}

int main(void) {
    printf("Compiles");
}
