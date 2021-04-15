
#include <stdlib.h>
#include <stdio.h>

#include "dll.h"
#include "scanner.h"
#include "parser.h"
#include "ast.h"

void tokenise(PSCANNER s, PDLLIST list) {
  int i = 0;
  
  list->s = 0;
  PDNODE b;
  while (1) {	
    PPAIR pair = malloc(sizeof(PAIR));
    nextPair(s, pair);

    PDNODE c = malloc(sizeof(DNODE));
    c->v = pair;
    if (list->s == 0) initDouble(list, c);
    else addAfterDouble(list, b, c);
    b = c;

    if (pair->token == END) break;
  }
  printDouble(list, printPair);
}

enum TOKEN token(char c, enum TOKEN ct) {
  if (c > 64 && c < 91 || c > 96 && c < 123) return ID;
  else if (c > 47 && c < 58) {
    if (ct == ID) return ID;
    else return NUM;
  }
  switch (c) {
  case (';'):
    return SEMI;
  case ('='):
    return ASGN;
  case ('+'):
    return ADD;
  case ('-'):
    return SUB;
  case ('*'):
    return MULT;
  case ('/'):
    return DIV;
  case ('('):
    return BRA;
  case (')'):
    return KET;
  default:
    return END;
  }
}

void nextPair(PSCANNER s, PPAIR pair) {
  // t - temp token
  // ct - current/expected token 
  enum TOKEN t, ct;
  char c;
  int i, j;
  int head = s->position;
  i = 0;
  ct = END;
  while (1) {
    // get character
    c = s->program[s->position];
		if (c == '\0') break;
    if (c == '\t' || c == '\n' || c == ' ') {
      // whitespace
      if (i == 0) {
        // start of token => increment 
        head++;
        s->position++;
        continue;
      }
      // it cuts the token, end
      break;
    }
    // get the type of token
    t = token(c, ct);
    if (i == 0) {
      // if it is the start, set to current token
      i = 1;
      ct = t;
    }
    // if there is a new token, end
    if (t != ct) break;
    // else next char
    s->position++;
  }
  pair->token = ct; 
  pair->lexeme = calloc(s->position-head-1, sizeof(char));
  j = 0;
  for (i = head; i < s->position; i++) {
    pair->lexeme[j] = s->program[i];
    j++;
  }
}

void printPair(void *pair) {
  printf("{%s,%s}", ((PPAIR)pair)->lexeme, tokenStr(((PPAIR)pair)->token));
}

char* tokenStr(enum TOKEN t) {
  switch (t) {
  case (END):
    return "END";
  case (ID):
    return "ID";
  case (NUM):
    return "NUM";
  case (SEMI):
    return "SEMI";
  case (ASGN):
    return "ASGN";
  case (ADD):
    return "ADD";
  case (SUB):
    return "SUB";
  case (MULT):
    return "MULT";
  case (DIV):
    return "DIV";
  case (BRA):
    return "BRA";
  case (KET):
    return "KET";
  default:
    return "NONE";
  }
}