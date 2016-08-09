#include <stdio.h>
#include <stdlib.h>
#include "cover.h"
#include "set.h"
#include "heap.h"

void
print_set_cover(Set s[], int n, int Home) {
	Heap *h;
	int i, index, count, result[n];
	// initialise an array to store the subsets needed
	count = 0;
	// initialise the universe set with all home indices within range
	// by taking the union of all sets AND create a heap sorted by the
	// size of each set (multiplying the key by -1 gives max heap)
	h = createHeap();
	for (i=0;i<n;i++) {
		insert(h, i, -1*(s[i].n));
	}
	index = removeMin(h);
	// extract the maximum everytime (not min!!) and update the whole
	// heap by substracting the key by number of items already covered
	// END the loop when the all covered (max in heap is zero)
	while (h->H[h->map[index]].key!=0) {
		result[count++] = index;
		for (i=0;i<h->n;i++) {
			changeKey(h, h->H[i].dataIndex, set_inter(&s[index],&s[h->H[i].dataIndex])->n);
		}
		if (h->n==0) {
			break;
		} else {
			index = removeMin(h);
		}
	}
	// then print subsets needed one by one
	for (i=0;i<count;i++) {
		printf("%d\n",Home+result[i]);
	}
}