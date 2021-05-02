#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

// Creates a new path
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES + 1);
        p->length = 0;
    }
    return p;
}

// Delets the path and frees up memory
void path_delete(Path **p) {
    if (*p) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

// Push a vertex to the path
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t t = 0; // T will hold the vertex at the top of the stack
    stack_peek(p->vertices, &t);

    // Only if stack push is successful we want to add edge weight
    if (stack_push(p->vertices, v)) {
        if (t != v) { // Make sure we dont add weight to the same vertex
            p->length += graph_edge_weight(G, t, v);
        }
        return true;
    }
    return false;
}

// Pop Vertex from path
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_pop(p->vertices, v)) {
        uint32_t t = 0; // T will hold the vertex at the top of the stack at this point
        stack_peek(p->vertices, &t);
        if (t != *v) { // Make sure we dont add weight to the same vertex
            p->length -= graph_edge_weight(G, t, *v);
        }
        return true;
    }
    return false;
}

// Returns number of vertices the path currently holds
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// Returns current length of the path
uint32_t path_length(Path *p) {
    return p->length;
}

// Copies contents of the src path to the destination path
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

// Print the current path
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %d\n", p->length);
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
    return;
}
