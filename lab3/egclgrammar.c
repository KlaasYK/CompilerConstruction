/* THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY LLnextgen. DO NOT EDIT */
#define LL_NTERMINALS 42
#define LL_NSETS 2
#define LL_SSETS 8
#define LLinset(LLx) (LLsets[LLx*LL_SSETS + (LLcsymb/8)] & (1<<(LLcsymb & 7)))
#define LL_SCANDONE(LLx) if (LLsymb != LLx) LLerror(LLx);
static int LLscnt[LL_NSETS+1], LLtcnt[LL_NTERMINALS];
static int LLcsymb;
#include <string.h>
static const char LLsets[] = {
	'\x06', 	'\x00', 	'\x80', 	'\x10', 	'\x21', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x80', 	'\x10', 	'\x01', 	'\x00', 	'\x00', 	'\x00', 
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
static const char *LLsymbolTable[] = {
"<EOF>", 
"<EOF>", "<SOH>", "<STX>", "<ETX>", 
"<EOT>", "<ENQ>", "<ACK>", "<BEL>", 
"<BS>", "<TAB>", "<NL>", "<VT>", 
"<FF>", "<CR>", "<SO>", "<SI>", 
"<DLE>", "<DC1>", "<DC2>", "<DC3>", 
"<DC4>", "<NAK>", "<SYN>", "<ETB>", 
"<CAN>", "<EM>", "<SUB>", "<ESC>", 
"<FS>", "<GS>", "<RS>", "<US>", 
"<SP>", "'!'", "'\"'", "'#'", 
"'$'", "'%'", "'&'", "'\''", 
"'('", "')'", "'*'", "'+'", 
"','", "'-'", "'.'", "'/'", 
"'0'", "'1'", "'2'", "'3'", 
"'4'", "'5'", "'6'", "'7'", 
"'8'", "'9'", "':'", "';'", 
"'<'", "'='", "'>'", "'?'", 
"'@'", "'A'", "'B'", "'C'", 
"'D'", "'E'", "'F'", "'G'", 
"'H'", "'I'", "'J'", "'K'", 
"'L'", "'M'", "'N'", "'O'", 
"'P'", "'Q'", "'R'", "'S'", 
"'T'", "'U'", "'V'", "'W'", 
"'X'", "'Y'", "'Z'", "'['", 
"'\\'", "']'", "'^'", "'_'", 
"'`'", "'a'", "'b'", "'c'", 
"'d'", "'e'", "'f'", "'g'", 
"'h'", "'i'", "'j'", "'k'", 
"'l'", "'m'", "'n'", "'o'", 
"'p'", "'q'", "'r'", "'s'", 
"'t'", "'u'", "'v'", "'w'", 
"'x'", "'y'", "'z'", "'{'", 
"'|'", "'}'", "'~'", "<DEL>", 
"'\x80'", "'\x81'", "'\x82'", "'\x83'", 
"'\x84'", "'\x85'", "'\x86'", "'\x87'", 
"'\x88'", "'\x89'", "'\x8A'", "'\x8B'", 
"'\x8C'", "'\x8D'", "'\x8E'", "'\x8F'", 
"'\x90'", "'\x91'", "'\x92'", "'\x93'", 
"'\x94'", "'\x95'", "'\x96'", "'\x97'", 
"'\x98'", "'\x99'", "'\x9A'", "'\x9B'", 
"'\x9C'", "'\x9D'", "'\x9E'", "'\x9F'", 
"'\xA0'", "'\xA1'", "'\xA2'", "'\xA3'", 
"'\xA4'", "'\xA5'", "'\xA6'", "'\xA7'", 
"'\xA8'", "'\xA9'", "'\xAA'", "'\xAB'", 
"'\xAC'", "'\xAD'", "'\xAE'", "'\xAF'", 
"'\xB0'", "'\xB1'", "'\xB2'", "'\xB3'", 
"'\xB4'", "'\xB5'", "'\xB6'", "'\xB7'", 
"'\xB8'", "'\xB9'", "'\xBA'", "'\xBB'", 
"'\xBC'", "'\xBD'", "'\xBE'", "'\xBF'", 
"'\xC0'", "'\xC1'", "'\xC2'", "'\xC3'", 
"'\xC4'", "'\xC5'", "'\xC6'", "'\xC7'", 
"'\xC8'", "'\xC9'", "'\xCA'", "'\xCB'", 
"'\xCC'", "'\xCD'", "'\xCE'", "'\xCF'", 
"'\xD0'", "'\xD1'", "'\xD2'", "'\xD3'", 
"'\xD4'", "'\xD5'", "'\xD6'", "'\xD7'", 
"'\xD8'", "'\xD9'", "'\xDA'", "'\xDB'", 
"'\xDC'", "'\xDD'", "'\xDE'", "'\xDF'", 
"'\xE0'", "'\xE1'", "'\xE2'", "'\xE3'", 
"'\xE4'", "'\xE5'", "'\xE6'", "'\xE7'", 
"'\xE8'", "'\xE9'", "'\xEA'", "'\xEB'", 
"'\xEC'", "'\xED'", "'\xEE'", "'\xEF'", 
"'\xF0'", "'\xF1'", "'\xF2'", "'\xF3'", 
"'\xF4'", "'\xF5'", "'\xF6'", "'\xF7'", 
"'\xF8'", "'\xF9'", "'\xFA'", "'\xFB'", 
"'\xFC'", "'\xFD'", "'\xFE'", "'\xFF'", 
"<EOF>", "BEGIN_TOK", "END_TOK", "COMMENT", 
"PROGRAM_TOK", "DOBEGIN_TOK", "DOEND_TOK", "IFBEGIN_TOK", 
"IFEND_TOK", "FUNCTION_TOK", "OR_OP", "AND_OP", 
"CAND_OP", "COR_OP", "ASSIGNMENT_OP", "PLUS_OP", 
"MUL_OP", "POW_OP", "COMPARE_OP", "TYPE_OP", 
"VAR_TOK", "VARIABLE", "NUMBER", "STRING", 
"BOOLEAN", "THEN_TOK", "CONSTANT_TOK", "COMMA", 
"SEMICOLON", "ALTGUARD", "FUNCNAME", "PROGRAMNAME", 
"IDENTIFIER", "NOT_TOK", "TYPE", "EOL", 
"ERROR", "DOT", "LPARREN", "RPARREN", 
"PROCEDURE_TOK", "WHITESPACE"};
const char *LLgetSymbol(int LLtoken) {
	if (LLtoken < -1 || LLtoken > 297 /* == LL_MAXTOKNO */)
		return (char *) 0;
	return LLsymbolTable[LLtoken+1];
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
char * file_name;
int linesread;

/* to keep track of errors */
int columnnr;
int linecount;

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

void LLmessage(int token) {
	switch (token) {
		case LL_MISSINGEOF:
		printf("%s:%d: Expected %s, found %s (%s).\n", file_name, linecount, LLgetSymbol(EOFILE), LLgetSymbol(LLsymb), yytext);
		break;
		case LL_DELETE:
		printf("%s:%d: Unexpected %s (%s).\n", file_name, linecount, LLgetSymbol(LLsymb), yytext);
		break;
		default:
		printf("%s:%d: Expected %s, found %s (%s).\n", file_name, linecount, LLgetSymbol(token), LLgetSymbol(LLsymb), yytext);
		break;
	}
	freeLines();
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	linecount = 0, columnnr = 0;
	
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [filename.c]\n", argv[0]);
		exit(-1);
  	}
	if (argc == 2) {
		file_name = argv[1];
		readFile(argv[1]);
		yyin = fopen(argv[1], "r");
	}
	
	parser();

	//Lees tot EOF
	/* int val = yylex();
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
	}*/

	if (argc == 2) {
		fclose(yyin);
	}

	printf("Parsing succesfull\n");
	
	freeLines();
	
	return EXIT_SUCCESS;
}




/*int main(int argc, char *argv[]) {
	parser();
	printf("Accepted\n");
	return 0;
}*/


/* EOF c FILE */

#line 306 "egclgrammar.c"
static void LL0_start(void);
static void LL1_header(void);
static void LL2_programbody(void);
static void LL3_functioncall(void);
static void LL0_start(void){
LLscnt[0]++;
LL1_header();
LLread();
LLscnt[0]--;
LL2_programbody();
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
static void LL2_programbody(void){
LLscnt[1]++;
LLtcnt[2]++;
LLtcnt[37]++;
LL_SCANDONE(257);/* BEGIN_TOK */
LLread();
LLscnt[1]--;
LL3_functioncall();
LLread();
LLtcnt[2]--;
LL_SCANDONE(258);/* END_TOK */
LLread();
LLtcnt[37]--;
LL_SCANDONE(293);/* DOT */
}
static void LL3_functioncall(void){
LLtcnt[23]++;
LLtcnt[28]++;
LL_SCANDONE(288);/* IDENTIFIER */
LLread();
LLtcnt[23]--;
LL_SCANDONE(279);/* STRING */
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

