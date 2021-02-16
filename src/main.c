
#include <stdio.h>
#include <stdlib.h>

#include "readf.h"
#include "dll.h"
#include "scanner.h"
#include "parser.h"

#define MAX_FILE 2048

void main(int argc, char **argv) {
  PSCANNER scanner = malloc(sizeof(SCANNER));
  scanner->position = 0;
  char program[MAX_FILE];
  readf(argv[1], program);
  
  scanner->program = program;
  
  printf("%s\n", program);
  
  PDLLIST list = malloc(sizeof(DLLIST));
  tokenise(scanner, list);

  PAST ast = malloc(sizeof(AST));
  parse(ast, list);
  printAST(ast);
  
  system("PAUSE");
}

