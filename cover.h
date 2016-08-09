/* Header file of set cover function
** Junwei Yang 667275
*/

#include "set.h"
#include "heap.h"

/* The function takes an array of sets and use a heap to store all the
** sets by the size of the set, and every time when a set with max size 
** is removed from the heap, all items in the heap will be reduced by the 
** number of what is already in the set just removed, and stop the loop
** when the size of max heap is zero, and print all the sets removed
** which are stored in an array
*/
void print_set_cover(Set s[], int n, int Home);