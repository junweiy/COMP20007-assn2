/* createHeap is used to create a heap with a max size of 1.
** insert function inserts the an item into the heap by creating a new
   item and pushing it to the next one of the last item and sift it up.
** peek function returns the data index of the root.
** peekkey function returns the key of the root.
** removeMin function removes the root by swapping the root the the last
   item then delete the last item and sift down the root.
** changeKey function modifies the key of the item of given data index.
** destroyHeap function frees the whole heap.
** siftup does the sifting up by swapping the item with its parents while
   it is not the root and it is less than its parent.
** sift down does the sifting down by swapping the item with the smaller
   child or the only child while the item has at least one child

** Student Name: Junwei Yang
** Student Number: 667275
*/

#ifndef HEAP_H
#define HEAP_H

typedef unsigned int uint;

typedef struct {
	float key; // the key for deciding position in heap
	uint dataIndex; // the payload index provided by the calling program
} HeapItem;

typedef struct heap {
	HeapItem *H; // the underlying array
	uint *map; // map[i] is index into H of location ith item in the heap
	uint n; // the number of items currently in the heap
	uint size; // the maximum number of items allowed in the heap
} Heap;

#endif

Heap *createHeap();
int insert(Heap *h, uint dataIndex, float key);
uint peek(Heap *h);
float peekKey(Heap *h);
uint removeMin(Heap *h);
void changeKey(Heap *h, uint dataIndex, int delta);
void destroyHeap(Heap *h);
void siftup(Heap *h, uint dataIndex);
void siftdown(Heap *h, uint dataIndex);
void swap(Heap *h, uint data1, uint data2);
uint findsmallerchild(Heap *h, uint dataIndex);