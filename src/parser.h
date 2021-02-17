#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#include "dll.h"
#include "scanner.h"


enum EXPT {
  PAIRT,
  BINT
};

typedef struct {
  enum EXPT expt;
  void *exp; // exp -> PAIR, BINARY
} EXP, *PEXP;

typedef struct {
  PEXP left;
  PEXP right;
  enum TOKEN op;
} BINEXP, *PBINEXP;

typedef struct {
  PEXP root;
} AST, *PAST;

typedef struct {
  PDNODE node;
} PARSER, *PPARSER;

void tokenise(PSCANNER scanner, PDLLIST list);

void parse(PAST ast, PDLLIST list);
void parseTerm(PPARSER p, PEXP e);
void parseFactor(PPARSER p, PEXP e);
void parseSingle(PPARSER p, PEXP e);

void printAST(PAST ast);
void printExpression(PEXP exp, int i);
void printOperator(enum TOKEN op, int i);
void printIndentation(int i);
void printBinary(PBINEXP be, int i);

void tokenise(PSCANNER scanner, PDLLIST list) {
  int i = 0;
  
  list->s = 0;
  PDNODE b;
  while (scanner->program[scanner->position]) {	
    PPAIR pair = malloc(sizeof(PAIR));
    nextPair(scanner, pair);

    PDNODE c = malloc(sizeof(DNODE));
    c->v = pair;
    if (list->s == 0) initDouble(list, c);
    else addAfterDouble(list, b, c);
    b = c;
  }
  printDouble(list, printPair);
}

void parse(PAST ast, PDLLIST list) {
  /*  
   *
   * TERM
   * : FACT
   * | FACT + FACT
   * ;
   *
   * FACT
   * : SING
   * | SING * SING
   * ;
   * 
   * SING
   * : NUM
   * | ( TERM )
   * ;
   *
   */

  PEXP exp = malloc(sizeof(EXP));
  ast->root = exp;
  PPARSER p = malloc(sizeof(PARSER));
  p->node = list->h;
  parseTerm(p, exp);
}


void parseTerm(PPARSER p, PEXP e) {
  printf("TERM\n");
  
  parseFactor(p, e);
  
  enum TOKEN t = ((PPAIR)p->node->n->v)->token;  
  while (t == ADD || t == SUB) {
    printf("FACT +|- FACT\n");
    
    // binary operation
    PBINEXP be = malloc(sizeof(BINEXP));

    PEXP left = malloc(sizeof(EXP));
    PEXP right = malloc(sizeof(EXP));

    // redo skip
    left->expt = e->expt;
    left->exp = e->exp;

    e->expt = BINT;
    e->exp = be;
    
    be->op = t;
    be->left = left;
    be->right = right;
    
    // shift node to right
    p->node = p->node->n->n;
    
    // right
    parseFactor(p, right);

    // check again
    t = ((PPAIR)p->node->n->v)->token;
  }
}

void parseFactor(PPARSER p, PEXP e) {  
  printf("FACT\n");

  // skip
  parseSingle(p, e);
  
  enum TOKEN t = ((PPAIR)p->node->n->v)->token;
  while (t == MULT || t == DIV) {
    printf("SING *|/ SING\n");

    // binary expression
    PBINEXP be = malloc(sizeof(BINEXP));
    
    PEXP left = malloc(sizeof(EXP));
    PEXP right = malloc(sizeof(EXP));

    // redo skip
    left->expt = e->expt;
    left->exp = e->exp;

    e->expt = BINT;
    e->exp = be;
    
    be->op = t;
    be->left = left;
    be->right = right;

    // shift node to right
    p->node = p->node->n->n;
    
    // right
    parseSingle(p, right);

    // check again
    t = ((PPAIR)p->node->n->v)->token;
  }
}

void parseSingle(PPARSER p, PEXP e) {
  printf("SING\n");
  e->expt = PAIRT;
  
  enum TOKEN t = ((PPAIR)p->node->v)->token;  
  if (t == NUM) {
    printf("NUM\n");
    e->exp = p->node->v;
  }
  else if (t == BRA) {
    printf("( TERM )\n");
    printf("(\n");
    p->node = p->node->n;
    parseTerm(p, e);
    printf(")\n");
    p->node = p->node->n;
  }
}

void printAST(PAST ast) {
  printExpression(ast->root, 0);
}

void printExpression(PEXP e, int i) {
  if (e->expt == BINT) {
    PBINEXP be = (PBINEXP)e->exp;
    printOperator(be->op, i);
    printExpression(be->left, i+1);
    printExpression(be->right, i+1);
  }
  else if (e->expt == PAIRT) {
    // SING => num
    printIndentation(i);
    PPAIR pair = (PPAIR)e->exp;
    char *s = pair->lexeme;
    printf("%s\n", s);
  }
}

void printOperator(enum TOKEN op, int i) {
  printIndentation(i);
  switch (op) {
  case (ADD):
    printf("+\n");
    break;
  case (SUB):
    printf("-\n");
    break;
  case (MULT):
    printf("*\n");
    break;
  case (DIV):
    printf("/\n");
    break;
  }
}

void printIndentation(int i) {
  int j;
  for (j = 0; j < i; j++) {
    printf("\t");
  }
}

#endif
