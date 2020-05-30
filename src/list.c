#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"


/* This function allows to create an empty chained list
   Return the list */

List createList() {
	List l = malloc(sizeof(struct cell));
	l->val = NULL;
	l->fo = NULL;
	return l;
}


/* This function indicates whether the chained list is empty or not
   Returns 1 if the list is empty
   Returns 0 otherwise */

int isEmpty(List l) {
	if(l->val == NULL)
		return 1;
	else
		return 0;
}


/* This function appends a value to the chained list
   The value is added to the end of the list
   Returns the list with the added value */

List append(List l, Pair p) {
	if(isEmpty(l)) {
		l->val = p;
	}
	else {
		List l2 = malloc(sizeof(struct cell));
		l2->fo = NULL;
		l2->val = p;
		List mem = l;
		while(mem->fo != NULL) {
			mem = mem->fo;
		}
		mem->fo = l2;
	}
	return l;
}


/* This function pops the last element of the list
   If the list is empty, it remains unchanged
   Returns the list */

List pop(List l) {
	if(isEmpty(l))
		return l;
	else {
		List mem = l, precmem = NULL;
		while(mem->fo != NULL) {
			precmem = mem;
			mem = mem->fo;
		}
		free(mem->val);
		mem->val = NULL;
		if(precmem != NULL) {
			precmem->fo = NULL;
			free(mem);
		}
		return l;
	}
}


/* This function completely deletes the list */

void deleteList(List l) {
	while(!isEmpty(l))
		pop(l);
	free(l);
	l = NULL;
}


/* This function displays the content of the list */

void displayList(List l) {
	if(isEmpty(l))
		printf("<empty list>\n");
	else {
		List mem;
		printf("[");
		for(mem = l; mem->fo != NULL; mem = mem->fo) {
			displayPair(mem->val);
			printf(", ");
		}
		displayPair(mem->val);
		printf("]\n");
	}
	fflush(stdout);
}


/* This function returns the size of a list */

int size(List l) {
	if(isEmpty(l)) {
		return 0;
	}
	else {
		List mem = l;
		int compteur = 1;
		while(mem->fo != NULL) {
			compteur++;
			mem = mem->fo;
		}
		return compteur;
	}
}


/* This function displays the content of a Pair */

void displayPair(Pair p) {
	printf("(%c, %d)", p->symb, p->nb);
}


/* This function allows to create a Pair object
   Returns the Pair */

Pair createPair(char symb, int nb) {
	Pair p = malloc(sizeof(struct pair));
	p->symb = symb;
	p->nb = nb;
	return p;
}
