/*
**
**
**
*/


#include <stdlib.h>
#include <stdio.h>
#include "cover.h"
#include "set.h"
#include "graph.h"
#include "dijkstra.h"

#define MAX 1000

int
validate(Graph *g) {
	// only check the connectivity of the graph
	int i;
	float x;
	graph_dfs(g, 0, graph_default_explore);
	for (i=0;i<g->number_of_vertices;i++) {
		if (g->vertices[i].data==(void*)0) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[])
{
	int H, S, ch, v, u, i, setcount=0;
	float dist;
	char buffer[MAX];
	Graph *g;
	// read the first line as H
	if (fgets(buffer, MAX, stdin)==NULL) {
		fprintf(stderr, "failed to read file!\n");
		exit(EXIT_FAILURE);
	}
	sscanf(buffer, "%d", &H);
	// then the next line as S
	if (fgets(buffer, MAX, stdin)==NULL) {
		fprintf(stderr, "failed to read file!\n");
		exit(EXIT_FAILURE);
	}
	sscanf(buffer, "%d", &S);
	g = graph_new(H+S);
	Set s[S]; // set an array of set here to avoid dynamic allocation
	// afterwards start to draw the graph from u to v with dist
	while (fgets(buffer, MAX, stdin)!=NULL) {
		sscanf(buffer, "%d %d %f", &v, &u, &dist);
		graph_add_edge(g, v, u, (void*)(&dist));
		graph_add_edge(g, u, v, (void*)(&dist));
	}
	// now validate if the graph is acceptable
	if (!validate(g)) {
		fprintf(stderr, "graph NOT GOOD!\n");
		exit(EXIT_FAILURE);
	}
	// then run dijkstra's algorithms on all school vertices
	i = H;
	while (setcount<S) {
		s[setcount++]=*dijkstra(g, i++, H, H+S);
	}
	// run cover set
	print_set_cover(s, setcount, H);
	// free the memory
	set_free(s);

	return 0;
}