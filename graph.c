/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for workshop 3 of COMP20007
**
** Andrew Turpin
** Tue 17 Mar 2015 19:13:47 AEDT
** Modified by Junwei Yang, Student Number: 667275
*/

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"

/*
** Create graph with number_of_vertices vertices
*/
Graph *
graph_new(int number_of_vertices) {
    assert(number_of_vertices > 0);
    int i;
    Graph *g = NULL;
    // malloc space for graph, vertices and edges in vertices and set max
    // nums of edges to 1
    g = (Graph*)malloc(sizeof(*g));
    g->vertices = (Vertex*)malloc(number_of_vertices*sizeof(*(g->vertices)));
    g->number_of_vertices = number_of_vertices;
    for (i=0;i<g->number_of_vertices;i++) {
        g->vertices[i].num_edges = 0;
        g->vertices[i].max_num_edges = 1;
        g->vertices[i].data = (void*)0;
        g->vertices[i].edges = (Edge*)malloc(sizeof(*(g->vertices[i].edges)));
    }

    return(g);
}

/*
** Add edge to g. 
*/
void  
graph_add_edge(Graph *g, Label v, Label u, void *data) {
    size_t size;
    void *temp;
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    // malloc space for temp
    temp = (void*)malloc(sizeof(void*));
    // reassign space if not enough
    if (g->vertices[v].num_edges>=g->vertices[v].max_num_edges) {
        g->vertices[v].max_num_edges *= 2;
        size = g->vertices[v].max_num_edges*sizeof(*(g->vertices[v].edges));
        g->vertices[v].edges = (Edge*)realloc(g->vertices[v].edges, size);
    }
    // if already exists do nothing
    if (graph_has_edge(g, v, u)) {
        return;
    }
    // copy data into the array and then increment the number
    temp = memcpy(temp, data, sizeof(void*));
    g->vertices[v].edges[g->vertices[v].num_edges].data = temp;
    g->vertices[v].edges[g->vertices[v].num_edges].u = u;
    g->vertices[v].num_edges++;
    
}

/*
** Delete edge from g. Only deletes one copy if there are multiple.
** Does nothing if u is not in v's list.
*/
void  
graph_del_edge(Graph *g, Label v, Label u) {
    int i,t;
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);
    // loop through every edge in vertice v
    for (i=0;i<g->vertices[v].num_edges;i++) {
        // if u is found continue to loop every edge and fill the place
        // due to deletion
        if (u==g->vertices[v].edges[i].u) {
            for (t=i+1;t<g->vertices[v].num_edges;t++) {
                g->vertices[v].edges[t-1].data = g->vertices[v].edges[t].data;
                g->vertices[v].edges[t-1].u = g->vertices[v].edges[t].u;
            }
            // after filling the hole, decrement the number and stop the loop
            g->vertices[v].num_edges--;
            break;
        }
    }
}

/*
** Return pointer to start of edge array for vertex v
** Set n to the number of items in the edge array.
*/
Edge *
graph_get_edge_array(Graph *g, Label v, int *num_edges) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

    *num_edges = g->vertices[v].num_edges;

    return g->vertices[v].edges;
}

/*
** Return 1 if (v,u) is in g
*/
int
graph_has_edge(Graph *g, Label v, Label u) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);
    
    int i;
    for (i=0;i<g->vertices[v].num_edges;i++) {
        if (u==g->vertices[v].edges[i].u) {
            return 1;
        }
    }

    return 0;
}


/*
** Set vertex's data to data
*/
void  
graph_set_vertex_data(Graph *g, Label v, void *data) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    g->vertices[v].data = data;
}


/*
** Simple explore for calling from dfs that doesn't actually do anything.
** Use as a template for writing your own explore() functions.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void 
graph_default_explore(Graph *g, Label v) {
    int i;
    if (g->vertices[v].data)
        return;

    g->vertices[v].data = (void *)1; // mark as visited

    for(i = 0 ; i < g->vertices[v].num_edges ; i++)
        graph_default_explore(g, g->vertices[v].edges[i].u);
}

/*
** Perform DFS beginning at v, calling pre() and post() as appropriate.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void 
graph_dfs(Graph *g, Label v, void (explore)(Graph *g, Label v)) {
    assert(g);
    assert(explore);
    assert(v >= 0 && v < g->number_of_vertices);

    explore(g, v);
}
