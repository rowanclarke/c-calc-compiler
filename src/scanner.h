#ifndef SCANNER_H
#define SCANNER_H

// TOKENS

enum TOKEN {
  NONE,
  END,
  ID,
  NUM,
  SEMI,
  ASGN,
  ADD,
  SUB,
  RECP,
  BRA,
  KET
};

enum OPER {
  OP_ASGN,
  OP_ADD,
  OP_SUB,
  OP_CAT,
  OP_RECP
};

typedef struct {
  enum TOKEN token;
  char *lexeme;
} PAIR, *PPAIR;

typedef struct {
  int position;
  char *program;
} SCANNER, *PSCANNER;

void tokenise(PSCANNER s, PDLLIST list);
enum TOKEN token(char c, enum TOKEN ct);
void nextPair(PSCANNER s, PPAIR pair);
void printPair(void *pair);
char* tokenStr(enum TOKEN t);
#endif
