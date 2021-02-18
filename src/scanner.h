#ifndef SCANNER_H
#define SCANNER_H

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

void tokenise(PSCANNER scanner, PDLLIST list);
enum TOKEN token(char c, enum TOKEN ct);
void nextPair(PSCANNER s, PPAIR pair);
void printPair(void *pair);

#endif
