#ifndef AST_H
#define AST_H

void printAST(PAST ast);
void printExpression(PEXP exp, int i);
void printOperator(enum TOKEN op, int i);
void printIndentation(int i);
void printBinary(PBINEXP be, int i);

#endif
