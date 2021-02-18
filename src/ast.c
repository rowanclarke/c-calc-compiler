
#include <stdio.h>

#include "dll.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"

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
