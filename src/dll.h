#ifndef DOUBLE_LINKED_LIST_H

#define DOUBLE_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct SNODE {
	struct SNODE *p; 	// point to previous node
    struct SNODE *n; 	// point to next node
	void *v;
} DNODE, *PDNODE;

typedef struct {
	PDNODE h; 	// point to head node
	int s;		// size of linked list
} DLLIST, *PDLLIST;

PDNODE initNode(void *v);
void initDouble(PDLLIST dll, PDNODE h);
void addAfterDouble(PDLLIST dll, PDNODE b, PDNODE n);
void removeDouble(PDLLIST dll, PDNODE n);
void printDouble(PDLLIST dll, void (*f)(void*));
	
PDNODE initNode(void *v) {
	PDNODE n = malloc(sizeof(DNODE));
	n->v = v;
	return n;
}

void initDouble(PDLLIST dll, PDNODE h) {
	dll->h = h;
	dll->s = 1;
}

void addAfterDouble(PDLLIST dll, PDNODE b, PDNODE n) {
    n->p = b;
	/*if (b->n) {
		n->n = b->n;
		n->n->p = n;
		}*/
    b->n = n;
    dll->s++;
}

void removeDouble(PDLLIST dll, PDNODE n) {
    n->p->n = n->n;
    n->n->p = n->p;
    free(n);
    dll->s--;
}

void printDouble(PDLLIST dll, void (*f)(void*)) {
	PDNODE p;
	int i;
	p = dll->h;
    printf("size: %d\n", dll->s);
    for (i = 0; i < dll->s; i++) {
        (*f)(p->v);
        printf("%s", i < dll->s-1 ? "<->" : "\n");
        p = p->n;
    }
}

#endif
