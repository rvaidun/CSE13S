#define OPTIONS "vui:o:"
#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <stdlib.h>
#include <string.h>

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    bool verbose, uint32_t *rec) {
    graph_mark_visited(G, v);
    for (uint32_t w = v + 1; w == v; w = (w + 1) % graph_vertices(G)) {
        if (graph_has_edge(G, v, w)) {
            if (!graph_visited(G, w)) {
                graph_mark_visited(G, w);
                if (path_push_vertex(curr, w, G)) {
                    *rec = *rec + 1;
                    dfs(G, w, curr, shortest, cities, outfile, verbose, rec);
                }
            }
        }
        if (path_length(curr) == graph_vertices(G)) {
            if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
                path_copy(shortest, curr);
            }
            if (verbose == true) {
                path_print(curr,outfile,cities);
            }
        }
    }
    graph_mark_unvisited(G, v);
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
    if (fscanf(in_fp, "%d", &num_cities) != 1) {
        printf("Error\n");
        return -1;
    }
    fflush(in_fp);

    graph = graph_create(num_cities, undirected);
    cities = malloc(num_cities * sizeof(char));

    for (uint32_t i = 0; i < num_cities; i++) {

        if (fgets(buffer, 1024, out_fp) != NULL) {
            cities[i] = strdup(buffer);
        } else {
            printf("Error\n");
            return -1;
        }
    }

    while ((temp = fscanf(in_fp, "%d %d %d", &i, &j, &k)) != EOF) {
        if (temp == 1) {
            graph_add_edge(graph, i, j, k);

        } else {
            printf("Malformed data \n");
            return -1;
        }
    }
    cur_path = path_create();
    short_path = path_create();
    dfs(graph, START_VERTEX, cur_path, short_path, cities, out_fp, verbose, &recursive_calls);
    fprintf(out_fp, "Total recursive calls: %d\n", recursive_calls);
}
