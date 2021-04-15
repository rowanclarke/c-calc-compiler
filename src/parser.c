
#include <stdio.h>
#include <stdlib.h>

#include "dll.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"

void next(PPARSER p) {
  printf("SKIP %s\n", ((PPAIR)p->node->v)->lexeme);
  p->node = p->node->n;
}

void eat(PPARSER p, enum TOKEN token) {
  printf("EAT %s\n", ((PPAIR)p->node->v)->lexeme);
  if (((PPAIR)p->node->v)->token != token) {
    printf("Syntax error: unexpected token \'%s\', expected \'%s\'\n", tokenStr(((PPAIR)p->node->v)->token), tokenStr(token));
  }
  p->node = p->node->n;
}

void parse(PAST ast, PDLLIST list) {
  /*  
   *
   * STMT
   * : EXP ; STMT
   * ;
   *
   * EXP
   * : ID ID
   * | ID = TERM
   * ;
   *
   * TERM
   * : FACT
   * | FACT + FACT
   * ;
   *
   * FACT
   * : SING
   * | SING SING
   * ;
   * 
   * SING
   * : LIT
   * | ( TERM )
   * ;
   *
   */

  PEXP exp = malloc(sizeof(EXP));
  ast->root = exp;
  PPARSER p = malloc(sizeof(PARSER));
  p->node = list->h;
  parseStatement(p, exp);
}

void parseStatement(PPARSER p, PEXP e) {
  printf("STMT\n");
  enum TOKEN t = ((PPAIR)p->node->v)->token;
  if (t != END) {
    e->strt = STMTT;
  
    PSTMTEXP stmt = malloc(sizeof(STMTEXP));
    e->exp = stmt;
    
    stmt->exp = malloc(sizeof(EXP));
    parseExpression(p, stmt->exp);
    
    eat(p, SEMI);
    stmt->next = malloc(sizeof(EXP));
    stmt->next->strt = ENDT;
    parseStatement(p, stmt->next);
  }
}

void parseExpression(PPARSER p, PEXP e) {
  enum TOKEN t = ((PPAIR)p->node->n->v)->token;
  if (t == ASGN) {
    printf("ASGN\n");
    e->strt = BINT;
    PBINEXP be = malloc(sizeof(BINEXP));
    be->op = t;
    e->exp = be;
    PEXP left = malloc(sizeof(EXP));
    left->strt = PAIRT;
    left->exp = p->node->v;
    PEXP right = malloc(sizeof(EXP));
    be->left = left;
    be->right = right;
    eat(p, ID);
    eat(p, ASGN);
    parseTerm(p, right);
  }
  else if (t == ID) {
    printf("DCLR\n");
    e->strt = DCLRT;
    PDCLREXP dclr = malloc(sizeof(DCLREXP));
    e->exp = dclr;
    dclr->set = (PPAIR)p->node->v;
    dclr->id = (PPAIR)p->node->n->v;
    eat(p, ID);
    eat(p, ID);
  }
}

void parseTerm(PPARSER p, PEXP e) {
  printf("TERM\n");
  // skip
  parseFactor(p, e);
  
  enum TOKEN t = ((PPAIR)p->node->v)->token;  
  while (t == ADD || t == SUB) {
    printf("ADD\n");
    // binary operation
    PBINEXP be = malloc(sizeof(BINEXP));

    PEXP left = malloc(sizeof(EXP));
    PEXP right = malloc(sizeof(EXP));

    // redo skip
    left->strt = e->strt;
    left->exp = e->exp;

    e->strt = BINT;
    e->exp = be;
    
    be->op = t;
    be->left = left;
    be->right = right;
    
    // shift node to right
    next(p); // + -
    
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
  
  enum TOKEN t = ((PPAIR)p->node->v)->token;
  while (t == MULT || t == DIV) {
    printf("MULT\n");
    // binary expression
    PBINEXP be = malloc(sizeof(BINEXP));
    
    PEXP left = malloc(sizeof(EXP));
    PEXP right = malloc(sizeof(EXP));

    // redo skip
    left->strt = e->strt;
    left->exp = e->exp;

    e->strt = BINT;
    e->exp = be;
    
    be->op = t;
    be->left = left;
    be->right = right;

    // shift node to right
    next(p); // * /

    // right
    parseSingle(p, right);

    // check again
    t = ((PPAIR)p->node->v)->token;
  }
}

void parseSingle(PPARSER p, PEXP e) {
  printf("SING\n");
  e->strt = PAIRT;
  
  enum TOKEN t = ((PPAIR)p->node->v)->token;  
  if (t == NUM) {
    printf("NUM\n");
    e->exp = p->node->v;
    eat(p, NUM);
  }
  else if (t == BRA) {
    printf("BRA\n");
    eat(p, BRA);
    parseTerm(p, e);
    eat(p, KET);
  }
}
