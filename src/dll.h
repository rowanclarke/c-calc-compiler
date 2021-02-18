#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

typedef struct SNODE {
  struct SNODE *p; 	// point to previous node
  struct SNODE *n; 	// point to next node
  void *v;
} DNODE, *PDNODE;

typedef struct {
  PDNODE h; 	        // point to head node
  int s;		// size of linked list
} DLLIST, *PDLLIST;

PDNODE initNode(void *v);
void initDouble(PDLLIST dll, PDNODE h);
void addAfterDouble(PDLLIST dll, PDNODE b, PDNODE n);
void removeDouble(PDLLIST dll, PDNODE n);
void printDouble(PDLLIST dll, void (*f)(void*));

#endif
