#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <stdlib.h>
#include <string.h>

#define OPTIONS "vui:o:"

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    bool verbose, uint32_t *rec) {
    uint32_t popped = 0;
    graph_mark_visited(G, v);
    // printf("%s Marked Visited\n", cities[v]);
    uint32_t w = 2;
    for (w = (v + 1) % graph_vertices(G); w != v; w = (w + 1) % graph_vertices(G)) {
        if (graph_has_edge(G, v, w)) {

            if (!graph_visited(G, w)) {
                // printf("Not Visited %s yet\n", cities[w]);
                if (path_push_vertex(curr, w, G)) {
                    *rec = *rec + 1;
                    // printf("Current Recursive Calls %d\n", *rec);
                    dfs(G, w, curr, shortest, cities, outfile, verbose, rec);
                }
            } else if (w == START_VERTEX) {
                path_push_vertex(curr, w, G);
                if (path_vertices(curr) == graph_vertices(G) + 1) {
                    if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
                        path_copy(shortest, curr);
                    }
                    if (verbose) {
                        path_print(curr, outfile, cities);
                    }
                }
                path_pop_vertex(curr, &popped, G);
            }
        }
    }
    path_pop_vertex(curr, &popped, G);
    graph_mark_unvisited(G, v);
    // printf("%s Marked Unvisited\n", cities[v]);
    return;
}
int main(void) {
    bool verbose = true;
    bool undirected = false;
    FILE *in_fp = stdin;
    FILE *out_fp = stdout;
    uint32_t recursive_calls = 0;
    uint32_t num_cities;
    char **cities;
    char buffer[1024];
    uint32_t i, j, k;
    int temp;
    Graph *graph;
    Path *cur_path;
    Path *short_path;
    if (fscanf(in_fp, "%d\n", &num_cities) != 1) {
        printf("Error in Reading Cities\n");
        return -1;
    }
    fflush(stdin);
    graph = graph_create(num_cities, undirected);
    cities = malloc(num_cities * sizeof(char *));

    for (uint32_t i = 0; i < num_cities; i++) {
        if (fgets(buffer, 1024, in_fp) != NULL) {
            strtok(buffer, "\n");
            cities[i] = strdup(buffer);
        }
    }

    while ((temp = fscanf(in_fp, "%d %d %d", &i, &j, &k)) != EOF) {
        if (temp == 3) {
            graph_add_edge(graph, i, j, k);

        } else {
            printf("Malformed data \n");
            return -1;
        }
    }
    cur_path = path_create();
    short_path = path_create();
    path_push_vertex(cur_path, START_VERTEX, graph);
    dfs(graph, START_VERTEX, cur_path, short_path, cities, out_fp, verbose, &recursive_calls);

    fprintf(out_fp, "Total recursive calls: %d\n", recursive_calls);
}
