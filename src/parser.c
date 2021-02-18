
#include <stdio.h>
#include <stdlib.h>

#include "dll.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"

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
