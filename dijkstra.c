/* implementation of dijkstra's SSSP
**
*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"
#include "set.h"
#include "dijkstra.h"

#define INFINITY 2147483647

Set 
*dijkstra(Graph *g, Label v, int Home, int n) {
	// for the school vertex v, find all indices for homes and put all into
	// a set
	Heap *H;
	Edge *Eu;
	Set *S;
	int i, usize;
	Label u;
	float R[n], delta;
	// create a heap to store the distance for every vertices
	// and an array to store dist values
	H = createHeap();
	for (i=0;i<n;i++) {
		if (i==v) {
			insert(H, i, 0);
			R[i]=0;
			continue;
		}
		insert(H, i, INFINITY);
		R[i] = INFINITY;
	}
	// then loop through the heap
	while (H->n) {
		// extract the min in the heap
		u = removeMin(H);
		// if dist of u exceeds 1km, stop the loop
		if (R[u]>1000) {
			break;
		}
		Eu = graph_get_edge_array(g, u, &usize);
		for (i=0;i<usize;i++) {
			if (R[Eu[i].u]>R[u]+ *(float*)(Eu[i].data)) {
				delta = R[u] + *(float*)(Eu[i].data) - R[Eu[i].u];
				changeKey(H, Eu[i].u, delta);
				R[Eu[i].u] = R[u]+ *(float*)(Eu[i].data);
			}
		}
	}
	// now add all home indices with in the range of 1km into the set
	S = set_new();
	for (i=0;i<Home;i++) {
		if (R[i]<=1000) {
			set_add(S, i);
		}
	}
	return S;
}
