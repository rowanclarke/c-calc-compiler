
#include <stdio.h>

#include "dll.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"

void printAST(PAST ast) {
  printExpression(ast->root, 0);
}

void printExpression(PEXP e, int i) {
  if (e->strt == STMTT) {
    PSTMTEXP stmt = (PSTMTEXP)e->exp;
    printExpression(stmt->exp, i);
    printExpression(stmt->next, i);
  }
  else if (e->strt == DCLRT) {
    PDCLREXP dclr = (PDCLREXP)e->exp;
    printIndentation(i);
    printf("(%s:%s)\n", dclr->set->lexeme, dclr->id->lexeme);
  }
  else if (e->strt == BINT) {
    PBINEXP be = (PBINEXP)e->exp;
    printOperator(be->op, i);
    printExpression(be->left, i+1);
    printExpression(be->right, i+1);
  }
  else if (e->strt == PAIRT) {
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
  case (ASGN):
    printf("=\n");
    break;
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
