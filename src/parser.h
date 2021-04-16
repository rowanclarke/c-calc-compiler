#ifndef PARSER_H
#define PARSER_H

enum STRT {
  STMTT,
  DCLRT,
  BINT,
  SINT,
  PAIRT,
  ENDT
};

typedef struct {
  enum STRT strt; // the structure of the expression
  void *exp; // exp -> PAIR, BINARY, STMTEXP
} EXP, *PEXP;

typedef struct {
  PEXP left;
  PEXP right;
  enum OPER op;
} BINEXP, *PBINEXP;

typedef struct {
  PEXP exp;
  enum OPER op;
} SINEXP, *PSINEXP;

typedef struct {
  PEXP exp;
  PEXP next;
} STMTEXP, *PSTMTEXP;

typedef struct {
  PPAIR set;
  PPAIR id;
} DCLREXP, *PDCLREXP;

typedef struct {
  PDNODE node;
} PARSER, *PPARSER;

typedef struct {
  PEXP root;
} AST, *PAST;

void next(PPARSER p);
void eat(PPARSER p, enum TOKEN token);
void parse(PAST ast, PDLLIST list);
void parseStatement(PPARSER p, PEXP e);
void parseExpression(PPARSER p, PEXP e);
void parseTerm(PPARSER p, PEXP e);
void parseFactor(PPARSER p, PEXP e);
void parseReciprocol(PPARSER p, PEXP e);
void parseSingle(PPARSER p, PEXP e);

#endif
