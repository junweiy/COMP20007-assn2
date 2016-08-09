#ifndef SET_H
#define SET_H

struct setitem {
	int index;  		// an index in the set
	struct setitem *next;	// a pointer points to the next item in the list
};

typedef struct setitem node;

typedef struct {
	node *head;			// head of the set (whose index is set id)
	int n;				// size of set
} Set;

#endif

Set *set_new();			  // create a set
void set_add(Set *s, int index);	  // insert item and maintain the order
node *set_find(Set *s, int index);	  // return the the item in set with index
Set *set_inter(Set *s1, Set *s2);	  // find the intersection of two sets
void set_free(Set *s); 				  // free the set