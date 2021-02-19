#ifndef PARSER_H
#define PARSER_H

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
  PDNODE node;
} PARSER, *PPARSER;

typedef struct {
  PEXP root;
} AST, *PAST;

void parse(PAST ast, PDLLIST list);
void parseTerm(PPARSER p, PEXP e);
void parseFactor(PPARSER p, PEXP e);
void parseSingle(PPARSER p, PEXP e);

#endif
