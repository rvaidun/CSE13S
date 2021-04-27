#define OPTIONS "vui:o:"
#include "graph.h"
#include <string.h>

int main(void) {
    bool verbose = false;
    bool undirected = false;
    uint32_t num_cities;
    char **cities;
    char buffer[1024];
    uint32_t i, j, k;
    Graph *graph;
    FILE *fp; = stdin;
    scanf("%d",&num_cities);

    graph = graph_create(num_cities,undirected)
    cities = malloc(num_cities * sizeof(char));
    for (uint32_t i = 0; i < num_cities; i++) {
	scanf("%s",buffer);
	cities[i] = strdup(buffer);
    }
    for (uint32_t i = 0; i < num_cities; i++) {
	scanf("%d %d %d", &i, &j, &k);
	graph_add_edge(G,i,j,k);
    }
}
