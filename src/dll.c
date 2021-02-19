
#include <stdio.h>
#include <stdlib.h>

#include "dll.h"

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
