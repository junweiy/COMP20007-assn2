/* Header file of dijkstra's algorithms
** Junwei Yang 667275
*/

#include "graph.h"
#include "heap.h"
#include "set.h"

/* The function runs dijkstra's algorithms on the given graph within
the range of 1km and return a set of HOME vertex IDs within 1km of the
SCHOOL position v
*/ 
Set *dijkstra(Graph *g, Label v, int Home, int n);