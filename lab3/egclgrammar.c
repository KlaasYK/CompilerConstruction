/* THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY LLnextgen. DO NOT EDIT */
#define LL_NTERMINALS 42
#define LL_NSETS 0
#define LL_SSETS 8
#define LLinset(LLx) (LLsets[LLx*LL_SSETS + (LLcsymb/8)] & (1<<(LLcsymb & 7)))
#define LL_SCANDONE(LLx) if (LLsymb != LLx) LLerror(LLx);
static int LLscnt[LL_NSETS+1], LLtcnt[LL_NTERMINALS];
static int LLcsymb;
#include <string.h>
static const char LLsets[] = {
	0
};
static const int LLindex[] = { 0,
	   0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
	   0,    1,    2,    3,    4,    5,    6,    7,
	   8,    9,   10,   11,   12,   13,   14,   15,
	  16,   17,   18,   19,   20,   21,   22,   23,
	  24,   25,   26,   27,   28,   29,   30,   31,
	  32,   33,   34,   35,   36,   37,   38,   39,
	  40,   41};
int LLsymb;
static int LLreissue;
int yylex(void);
static int LLlexerWrapper(void) {
	if (LLreissue == -2 /* LL_NEW_TOKEN */) {
		return yylex();
	} else {
		int LLretval = LLreissue;
		LLreissue = -2 /* LL_NEW_TOKEN */;
		return LLretval;
	}
}
void LLmessage(int);
static void LLread(void) { LLcsymb = LLindex[(LLsymb = LLlexerWrapper()) + 1]; }
static int LLskip(void) {
	int LL_i;
	if (LLcsymb >= 0) {
		if (LLtcnt[LLcsymb] != 0) return 0;
		for (LL_i = 0; LL_i < LL_NSETS; LL_i++)
			if (LLscnt[LL_i] != 0 && LLinset(LL_i))
				return 0;
	}

	for (;;) {
		LLmessage(0 /* LL_DELETE */);
		while ((LLcsymb = LLindex[(LLsymb = LLlexerWrapper()) + 1]) < 0) LLmessage(0 /* LL_DELETE */);
		if (LLtcnt[LLcsymb] != 0)
			return 1;
		for (LL_i = 0; LL_i < LL_NSETS; LL_i++)
			if (LLscnt[LL_i] != 0 && LLinset(LL_i))
				return 1;
	}
}
static void LLerror(int LLtoken) {
	if (LLtoken == 256 /* EOFILE */) {
		LLmessage(-1 /* LL_MISSINGEOF */);
		while (LLindex[(LLsymb = LLlexerWrapper()) + 1] != 0) /*NOTHING*/ ;
		return;
	}
	LLtcnt[LLindex[LLtoken + 1]]++;
	LLskip();
	LLtcnt[LLindex[LLtoken + 1]]--;
	if (LLsymb != LLtoken) { LLreissue = LLsymb; LLmessage(LLtoken); }
}
#include "egclgrammar.h"
#line 6 "egclgrammar.g"

/* BEGIN C FILE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE * yyin;
extern char * yytext;

char **lines;
int linesread;

void readFile(char *filename) {
	FILE * fin = fopen(filename, "r");
	int i = 0;
	size_t len = 0;
	ssize_t read = 0;
	/* TODO: remove hardcoded limit */
	lines = malloc(1000 * sizeof(char*)); 
	
	while ( getline( &(lines[i]), &len, fin) != -1 ) {
		i++;
		linesread++;
	}
	linesread++;
	fclose(fin);
}

void freeLines() {
	int i;
	for (i=0; i < linesread; ++i) {
		free(lines[i]);
	}
	free(lines);
	if (yyin != NULL) {
		fclose(yyin);
	}
	/* flex buffers */
	yylex_destroy();
}

void printLexError(char *illchar, int line, int column) {
	int i = 0;
	printf("\nError on line %4d: %s", line, lines[line]);
	for (i; i < column + 20; i++) {
		printf(" ");
	}
	printf("^\n");
	printf("Illegal character (%s) detected at column %d\n", illchar, column);
	freeLines();
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	int linecount = 0, columnnr = 0;
	
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [filename.c]\n", argv[0]);
		exit(-1);
  	}
	if (argc == 2) {
		readFile(argv[1]);
		yyin = fopen(argv[1], "r");
	}

	//Lees tot EOF
	int val = yylex();
	while (val > EOF) {
		switch (val) {
			case COMMENT: printf("\n"); linecount++; columnnr = 0; break;
			case IDENTIFIER: printf ("||%s|| ", yytext); columnnr += strlen(yytext); break;
			case EOL : printf("\n"); linecount++; columnnr = 0; break;
			case WHITESPACE: columnnr += strlen(yytext); break;
			case ERROR : printLexError(yytext, linecount, columnnr); break;
			default: printf ("|%s| ", yytext); columnnr += strlen(yytext);
		}
	
		val = yylex();
	}

	if (argc == 2) {
		fclose(yyin);
	}

	printf("Lexing succesfull\n");
	
	freeLines();
	
	return EXIT_SUCCESS;
}




/*int main(int argc, char *argv[]) {
	parser();
	printf("Accepted\n");
	return 0;
}*/

void LLmessage(int token) {
	printf("Parse error: %d\n", token);
	exit(EXIT_FAILURE);
}

/* EOF c FILE */

#line 205 "egclgrammar.c"
static void LL0_start(void);
static void LL1_header(void);
static void LL0_start(void){
LL1_header();
}
static void LL1_header(void){
LLtcnt[32]++;
LLtcnt[28]++;
LL_SCANDONE(260);/* PROGRAM_TOK */
LLread();
LLtcnt[32]--;
LL_SCANDONE(288);/* IDENTIFIER */
LLread();
LLtcnt[28]--;
LL_SCANDONE(284);/* SEMICOLON */
}
void parser(void) {
	memset(LLscnt, 0, LL_NSETS * sizeof(int));
	memset(LLtcnt, 0, LL_NTERMINALS * sizeof(int));
	LLtcnt[0]++;
	LLsymb = 0;
	LLreissue = -2 /* LL_NEW_TOKEN */;
	LLread();
	LL0_start();
	LLread();
	if (LLcsymb != 0) LLerror(256 /* EOFILE*/);
}

