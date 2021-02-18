
#include <stdio.h>
#include <stdlib.h>

#include "dll.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"

#define MAX_FILE 2048

void readf(char *filename, char *dest) {
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) perror("Error opening file");
  fscanf(fp, "%[^\0]", dest);
  fclose(fp);
}

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

