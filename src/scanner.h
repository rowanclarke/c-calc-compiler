#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

// TOKENS

enum TOKEN {
  END,
  ID,
  NUM,
  ASGN,
  ADD,
  SUB,
  MULT,
  DIV,
  BRA,
  KET
};

typedef struct {
  enum TOKEN token;
  char *lexeme;
} PAIR, *PPAIR;

typedef struct {
  int position;
  char *program;
} SCANNER, *PSCANNER;

enum TOKEN token(char c, enum TOKEN ct);
void nextPair(PSCANNER s, PPAIR pair);
void printPair(void *pair);

void nextPair(PSCANNER s, PPAIR pair) {
  // t - temp token
  // ct - current/expected token 
  enum TOKEN t, ct;
  char c;
  int i, j;
  int head = s->position;
  i = 0;
  do { // while there is a char
    // get first character of token
    c = s->program[s->position];
		
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
  } while (c);
  pair->token = ct;
  pair->lexeme = calloc(s->position-head-1,sizeof(char));
  j = 0;
  for (i = head; i < s->position; i++) {
    pair->lexeme[j] = s->program[i];
    j++;
  }
}

enum TOKEN token(char c, enum TOKEN ct) {
  if (c > 64 && c < 91 || c > 96 && c < 123) return ID;
  else if (c > 47 && c < 58) {
    if (ct == ID) return ID;
    else return NUM;
  }
  switch (c) {
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

void printPair(void *pair) {
  printf("{%s,%d}", ((PPAIR)pair)->lexeme, ((PPAIR)pair)->token);
}

#endif
