
#include <stdio.h>
#include <stdlib.h>

#include "dll.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"

#define MAX_FILE 2048

void read(char *filename, char *dest) {
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL) perror("Error opening file");
  fscanf(fp, "%[^\0]", dest);
  fclose(fp);
}

void main(int argc, char **argv) {
  PSCANNER scanner = malloc(sizeof(SCANNER));
  scanner->position = 0;
  scanner->program = calloc(MAX_FILE, sizeof(char));

  read(argv[1], scanner->program);
  
  printf("%s\n", scanner->program);

  PDLLIST list = malloc(sizeof(DLLIST));
  tokenise(scanner, list);
	
  PAST ast = malloc(sizeof(AST));
  parse(ast, list);
  printAST(ast);
	
  system("pause");
}

