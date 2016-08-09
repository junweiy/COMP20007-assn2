/* Implementation of the minimum heap structure
** Student Name: Junwei Yang
** Student Number: 667275
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

#define HEAP_SUCCESS 1
#define HEAP_FAIL 0
#define LEFT_CHILD(x) (2*x+1)
#define RIGHT_CHILD(x) (2*x+2)

Heap*
createHeap() {
	// create three arrays, malloc all of them and initialise
	Heap *h;
	HeapItem *H;
	uint *map;
	h = (Heap*)malloc(sizeof(*h));
	H = (HeapItem*)malloc(sizeof(*H));
	map = (uint*)malloc(sizeof(uint));
	h->map = map;
	h->H = H;
	h->n = 0;
	h->size = 1;
	return h;
}

int
insert(Heap *h, uint dataIndex, float key) {
	HeapItem *temp;
	// check if the position of new item is already occupied
	if (dataIndex<h->n && h->map[dataIndex]<h->n) {
		fprintf(stderr,"failed\n");
		return HEAP_FAIL;
	}
	// check if there's enough place for new heap items
	while (dataIndex>=h->size) {
		h->size *= 2;
		h->H = (HeapItem*)realloc(h->H, h->size * sizeof(*(h->H)));
		h->map = (uint*)realloc(h->map, h->size * sizeof(uint));
	}
	assert(h->H);
	assert(h->map);
	// create a temp heapitem pointer and insert to the place of 
	// position in H array and sift it up
	temp = (HeapItem*)malloc(sizeof(*temp));
	assert(temp);
	temp->key = key;
	temp->dataIndex = dataIndex;
	h->map[dataIndex] = h->n;
	h->H[h->n++] = *temp;
	siftup(h,dataIndex);
	return HEAP_SUCCESS;
}

uint
peek(Heap *h) {
	assert(h->n!=0);
	return h->H[0].dataIndex;
}

float
peekKey(Heap *h) {
	assert(h->n!=0);
	return h->H[0].key;
}

uint
removeMin(Heap *h) {
	assert(h->n!=0);
	int dataIndex;
	dataIndex = peek(h);
	// push the last item into the root
	swap(h, peek(h),h->H[h->n-1].dataIndex);
	// start doing the deleting
	h->n--;
	// if there is any remaining item, sift down the root
	if (h->n>0) {
		siftdown(h,peek(h));
	}
	return dataIndex;
}

void
changeKey(Heap *h, uint dataIndex, int delta) {
	// change the key and do either a siftup or siftdown depending
	// on the sign of delta
	int prev_key;
	prev_key = h->H[h->map[dataIndex]].key;
	h->H[h->map[dataIndex]].key += delta;
	if (delta>0) {
		siftdown(h, dataIndex);
	} else if (delta<0) {
		siftup(h, dataIndex);
	} else {
		return;
	}
}

void
destroyHeap(Heap *h) {
	free(h->H);
	free(h->map);
	free(h);
}

void
siftup(Heap *h, uint dataIndex) {
	// swap the parent and itself until either itself reaches the root
	// or it's greater than or equal to its parent
	float key, parentkey;
	uint pos;
	key = h->H[h->map[dataIndex]].key;
	pos = h->map[dataIndex];
	if (pos>0) {
		parentkey = h->H[(pos-1)/2].key;
	}
	// stop sifting up either when it reaches the root or its key is
	// greater than the key of its parent
	while (pos>0 && key<parentkey) {
		swap(h,h->H[pos].dataIndex,h->H[(pos-1)/2].dataIndex);
		// test if it already reached the root, if not update for next loop
		if ((pos-1)/2>0) {
			pos = (pos-1)/2;
			key = h->H[pos].key;
			parentkey = h->H[(pos-1)/2].key;
		} else {
			return;
		}
	}
}

void
siftdown(Heap *h, uint dataIndex) {
	// swap itself with the smaller child until it either has no child
	// or it's less than or equal to both children

	// if no children do nothing
	if (LEFT_CHILD(h->map[dataIndex])==h->n) {
		return;
	}
	// process two children for the first run
	uint smallerchild, pos;
	float key, childkey;
	smallerchild = findsmallerchild(h, dataIndex);
	key = h->H[h->map[dataIndex]].key;
	childkey = h->H[smallerchild].key;
	pos = h->map[dataIndex];
	// under the condition it has at least one child and 
	// its key is greater than the key of smaller child
	while (LEFT_CHILD(pos)<h->n && key>childkey) {
		// swap with the smaller child
		swap(h, h->H[pos].dataIndex, h->H[smallerchild].dataIndex);
		// update smaller child
		pos = smallerchild;
		// update the child of smaller child for next loop
		// test the size of pos in case of error
		if (LEFT_CHILD(pos)<h->n) {
			smallerchild = findsmallerchild(h, h->H[pos].dataIndex);
			key = h->H[pos].key;
			childkey = h->H[smallerchild].key;
		} else {
			break;
		}
	}
}

void
swap(Heap *h, uint data1, uint data2) {
	// swap pointer in heap items
	HeapItem temp;
	uint tempi;
	temp = h->H[h->map[data1]];
	h->H[h->map[data1]] = h->H[h->map[data2]];
	h->H[h->map[data2]] = temp;
	// then swap what maps are pointing at
	tempi = h->map[data1];
	h->map[data1] = h->map[data2];
	h->map[data2] = tempi;
}

uint
findsmallerchild(Heap *h, uint dataIndex) {
	// if there is only one child return the position of child in H
	// otherwise return the larger one
	// that is H[child].dataIndex = dataIndex 
	uint smallerchild, lchild, rchild;
	lchild = LEFT_CHILD(h->map[dataIndex]);
	rchild = RIGHT_CHILD(h->map[dataIndex]);
	if (lchild==h->n-1) {
		smallerchild = lchild;
	} else {
		if (h->H[lchild].key < h->H[rchild].key) {
			smallerchild = lchild;
		} else {
			smallerchild = rchild;
		}
	}
	return smallerchild;
}