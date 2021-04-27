#define OPTIONS "vui:o:"
#include "graph.h"
#include <string.h>

int main(void) {
    bool verbose = false;
    bool undirected = false;
    FILE *in_fp; = stdin;
    FILE *out_fp; = stdout;

    uint32_t num_cities;
    char **cities;
    char buffer[1024];
    uint32_t i, j, k;
    int temp;
    Graph *graph;
    if (fscanf(fp,"%d",&num_cities) != 1) {
	printf("Error\n");
	return -1;
    }
    fflush(fp);

    graph = graph_create(num_cities,undirected)
    cities = malloc(num_cities * sizeof(char));

    for (uint32_t i = 0; i < num_cities; i++) {

	if (fgets(buffer, 1024, fp) != NULL) {
	    cities[i] = strdup(buffer)
	} else {
	    printf("Error\n");
	    return -1;
	}
    }

    while( temp = fscanf(fp,"%d %d %d", &i, &j, &k) != EOF) {
	if (temp ==  1) {
	    graph_add_edge(G,i,j,k);

	} else {
	    printf("Malformed data \n");
	    return -1
	}

    }
}
