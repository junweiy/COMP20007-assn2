#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "set.h"

#define YES 1
#define NO 0

Set
*set_new() {
	// create a new set with one item
	Set *s;
	s = (Set*)malloc(sizeof(*s));
	s->head = NULL;
	s->n = 0;
	return s;
}

void
set_add(Set *s, int index) {
	assert(s!=NULL);
	// add one item into the set while maintaining the order
	// and increment the set size
	node *temp, *nxtnode, *prev;
	temp = (node*)malloc(sizeof(*temp));
	temp->index = index;
	nxtnode = s->head;
	s->n++;
	// insert if empty
	if (nxtnode==NULL) {
		temp->index = index;
		temp->next = NULL;
		s->head = temp;
		return;
	}
	// if insert at head
	if (index<=nxtnode->index) {
		temp->next = nxtnode;
		s->head = temp;
		return;
	}
	// look for the place to insert
	while (index>nxtnode->index) {
		prev = nxtnode;
		nxtnode = nxtnode->next;
		if (nxtnode==NULL) {
			break;
		}
	}
	// insert the new item into correct place
	prev->next = temp;
	temp->next = nxtnode;
}

node
*set_find(Set *s, int index) {
	assert(s!=NULL);
	// return the pointer of node with given index if found, else return null
	node *temp;
	temp = s->head;
	while (temp!=NULL) {
		if (temp->index == index) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

Set
*set_inter(Set *s1, Set *s2) {
	assert(s1!=NULL && s2!=NULL);
	Set *smallerset, *largerset, *s;
	node *temp;
	// find the smallest set first
	if (s1->n<s2->n) {
		smallerset = s1;
		largerset = s2;
	} else {
		smallerset = s2;
		largerset = s1;
	}
	s = (Set*)malloc(sizeof(*s));
	s = set_new();
	// return NULL if smallest set is empty
	if (smallerset->n==0) {
		return s;
	}
	temp = smallerset->head;
	// add all items existing in both sets to another set
	while (temp!=NULL) {
		if (set_find(largerset, temp->index)!=NULL) {
			set_add(s, temp->index);
		}
		temp = temp->next;
	}
	return s;
}

void
set_free(Set *s) {
	// free the set
	node *prev, *temp;
	temp = s->head;
	while (temp!=NULL) {
		prev = temp;
		temp = temp->next;
		free(prev);
	}
	free(s);
}