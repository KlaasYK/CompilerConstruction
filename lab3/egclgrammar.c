/* THIS FILE HAS BEEN AUTOMATICALLY GENERATED BY LLnextgen. DO NOT EDIT */
#define LL_NTERMINALS 38
#define LL_NSETS 21
#define LL_SSETS 8
#define LLinset(LLx) (LLsets[LLx*LL_SSETS + (LLcsymb/8)] & (1<<(LLcsymb & 7)))
#define LL_SCANDONE(LLx) if (LLsymb != LLx) LLerror(LLx);
static int LLscnt[LL_NSETS+1], LLtcnt[LL_NTERMINALS];
static int LLcsymb;
#include <string.h>
static const char LLsets[] = {
	'\x00', 	'\x00', 	'\x80', 	'\x80', 	'\x08', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x78', 	'\x9F', 	'\x82', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x82', 	'\x80', 	'\x08', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x8A', 	'\x80', 	'\x08', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x03', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x8E', 	'\x80', 	'\x08', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x8F', 	'\x80', 	'\x08', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x9F', 	'\x82', 	'\x08', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x9F', 	'\x82', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x30', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x48', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x30', 	'\x9F', 	'\x82', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x50', 	'\x06', 	'\x40', 	'\x80', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 
	'\x50', 	'\x7E', 	'\xDF', 	'\x86', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x00', 	'\x90', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\xF8', 	'\x9F', 	'\x92', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x50', 	'\x7E', 	'\xDF', 	'\xC6', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x82', 	'\x83', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x50', 	'\x06', 	'\xC2', 	'\x93', 	'\x09', 	'\x00', 	'\x00', 	'\x00', 
	'\x00', 	'\x00', 	'\x80', 	'\x03', 	'\x00', 	'\x00', 	'\x00', 	'\x00', 
	'\x56', 	'\x07', 	'\x40', 	'\x88', 	'\x20', 	'\x00', 	'\x00', 	'\x00', 
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
	  32,   33,   34,   35,   36,   37};
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
"<EOF>", "BEGIN_TOK", "END_TOK", "PROGRAM_TOK", 
"DOBEGIN_TOK", "DOEND_TOK", "IFBEGIN_TOK", "IFEND_TOK", 
"FUNCTION_TOK", "PRINT_TOK", "READ_TOK", "OR_OP", 
"AND_OP", "CAND_OP", "COR_OP", "ASSIGNMENT_OP", 
"PLUS_OP", "MIN_OP", "MUL_OP", "POW_OP", 
"COMPARE_OP", "TYPE_OP", "VAR_TOK", "NUMBER", 
"STRING", "BOOLEAN", "THEN_TOK", "CONSTANT_TOK", 
"COMMA", "SEMICOLON", "ALTGUARD", "IDENTIFIER", 
"NOT_TOK", "TYPE", "DOT", "LPARREN", 
"RPARREN", "PROCEDURE_TOK"};
const char *LLgetSymbol(int LLtoken) {
	if (LLtoken < -1 || LLtoken > 293 /* == LL_MAXTOKNO */)
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
	if (yyin != NULL) {
		fclose(yyin);
		yyin = NULL;
	}
	/* flex buffers */
	yylex_destroy();
}

void printLexError(char *illchar, int line, int column) {
	int i = 0, k;
	printf("\n");
	k = printf("Error on line %d: ", line+1);
	printf("%s", lines[line]);
	for (i; i < column + k; i++) {
		printf(" ");
	}
	printf("^\n");
	printf("Illegal character (%s) detected at column %d\n", illchar, column+1);
	freeLines();
	exit(EXIT_FAILURE);
}

void LLmessage(int token) {
	int i = 0, k, c;
	printf("\n");
	k = printf("Error on line %d: ", linecount+1);
	c = columnnr - strlen(yytext);
	printf("%s", lines[linecount]);
	for (i; i < c + k; i++) {
		printf(" ");
	}
	printf("^\n");
	switch (token) {
		case LL_MISSINGEOF:
		printf("Expected %s, found %s (%s).\n", LLgetSymbol(EOFILE), LLgetSymbol(LLsymb), yytext);
		break;
		case LL_DELETE:
		printf("Unexpected %s (%s).\n", LLgetSymbol(LLsymb), yytext);
		break;
		default:
		printf("Expected %s, found %s (%s).\n", LLgetSymbol(token), LLgetSymbol(LLsymb), yytext);
		break;
	}
	freeLines();
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	linecount = 0, columnnr = 0;
	printf("Extended Guarded Command Language Compiler.\n");
	if (argc > 2) {
		fprintf(stderr, "Usage: %s [filename.c]\n", argv[0]);
		exit(-1);
  	}
	if (argc == 2) {
		file_name = argv[1];
		printf("Compiling file: %s\n",file_name);
		readFile(argv[1]);
		yyin = fopen(argv[1], "r");
	}
	
	parser();

	if (argc == 2) {
		fclose(yyin);
		yyin = NULL;
	}

	printf("Parsing succesfull\n");
	
	freeLines();
	
	return EXIT_SUCCESS;
}

/* EOF c FILE */

#line 315 "egclgrammar.c"
static void LL0_rootexpr(void);
static void LL1_powbase(void);
static void LL2_factor2(void);
static void LL3_factor(void);
static void LL4_term2(void);
static void LL5_term(void);
static void LL6_sumexpr2(void);
static void LL7_sumexpr(void);
static void LL8_relexpr2(void);
static void LL9_relexpr(void);
static void LL10_notexpr(void);
static void LL11_andexpr2(void);
static void LL12_andexpr(void);
static void LL13_expr2(void);
static void LL14_expr(void);
static void LL15_guardedcommand(void);
static void LL16_guardedcommandset(void);
static void LL17_identifierarray(void);
static void LL18_functioncall(void);
static void LL19_assignmentcall(void);
static void LL20_dostatement(void);
static void LL21_ifstatement(void);
static void LL22_printable(void);
static void LL23_printcall(void);
static void LL24_readcall(void);
static void LL25_call(void);
static void LL26_declaration(void);
static void LL27_statement(void);
static void LL28_parameterset(void);
static void LL29_variable(void);
static void LL30_statementsetV2(void);
static void LL31_statementset(void);
static void LL32_function(void);
static void LL33_procedure(void);
static void LL34_constant_def(void);
static void LL35_programbody(void);
static void LL36_header(void);
static void LL37_start(void);
static void LL0_rootexpr(void){
LL_0:
switch (LLcsymb) {
case 35:/* LPARREN */
LLscnt[0]--;
LLscnt[1]++;
LLtcnt[36]++;
LL_SCANDONE(291);/* LPARREN */
LLread();
LLscnt[1]--;
LL14_expr();
LLtcnt[36]--;
LL_SCANDONE(292);/* RPARREN */
LLread();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 31:/* IDENTIFIER */
LLscnt[0]--;
LLtcnt[35]++;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LL_1:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_1;
LLtcnt[35]--;
break;
case 11:/* OR_OP */
case 12:/* AND_OP */
case 13:/* CAND_OP */
case 14:/* COR_OP */
case 16:/* PLUS_OP */
case 17:/* MIN_OP */
case 18:/* MUL_OP */
case 19:/* POW_OP */
case 20:/* COMPARE_OP */
case 26:/* THEN_TOK */
case 28:/* COMMA */
case 29:/* SEMICOLON */
case 36:/* RPARREN */
LLtcnt[35]--;
break;
case 35:/* LPARREN */
LLtcnt[35]--;
LL18_functioncall();
LLread();
}
break;
case 23:/* NUMBER */
LLscnt[0]--;
LL_SCANDONE(279);/* NUMBER */
LLread();
break;
}
}
static void LL1_powbase(void){
LL_0:
switch (LLcsymb) {
case 17:/* MIN_OP */
LLscnt[2]--;
LLscnt[0]++;
LL_SCANDONE(273);/* MIN_OP */
LLread();
LL0_rootexpr();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 23:/* NUMBER */
case 31:/* IDENTIFIER */
case 35:/* LPARREN */
LLscnt[2]--;
LLscnt[0]++;
LL0_rootexpr();
break;
}
}
static void LL2_factor2(void){
LL_0:
switch (LLcsymb) {
case 19:/* POW_OP */
LLtcnt[19]--;
LLscnt[2]++;
LLtcnt[19]++;
LL_SCANDONE(275);/* POW_OP */
LLread();
LL1_powbase();
LL2_factor2();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 11:/* OR_OP */
case 12:/* AND_OP */
case 13:/* CAND_OP */
case 14:/* COR_OP */
case 16:/* PLUS_OP */
case 17:/* MIN_OP */
case 18:/* MUL_OP */
case 20:/* COMPARE_OP */
case 26:/* THEN_TOK */
case 28:/* COMMA */
case 29:/* SEMICOLON */
case 36:/* RPARREN */
LLtcnt[19]--;
break;
}
}
static void LL3_factor(void){
LLscnt[2]++;
LLtcnt[19]++;
LL1_powbase();
LL2_factor2();
}
static void LL4_term2(void){
LL_0:
switch (LLcsymb) {
case 18:/* MUL_OP */
LLtcnt[18]--;
LLscnt[3]++;
LLtcnt[18]++;
LL_SCANDONE(274);/* MUL_OP */
LLread();
LLscnt[3]--;
LL3_factor();
LL4_term2();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 11:/* OR_OP */
case 12:/* AND_OP */
case 13:/* CAND_OP */
case 14:/* COR_OP */
case 16:/* PLUS_OP */
case 17:/* MIN_OP */
case 20:/* COMPARE_OP */
case 26:/* THEN_TOK */
case 28:/* COMMA */
case 29:/* SEMICOLON */
case 36:/* RPARREN */
LLtcnt[18]--;
break;
}
}
static void LL5_term(void){
LLtcnt[18]++;
LL3_factor();
LL4_term2();
}
static void LL6_sumexpr2(void){
LL_0:
switch (LLcsymb) {
case 16:/* PLUS_OP */
LLscnt[4]--;
LLscnt[5]++;
LLscnt[4]++;
LL_SCANDONE(272);/* PLUS_OP */
LLread();
LLscnt[5]--;
LL5_term();
LL6_sumexpr2();
break;
case 17:/* MIN_OP */
LLscnt[4]--;
LLscnt[5]++;
LLscnt[4]++;
LL_SCANDONE(273);/* MIN_OP */
LLread();
LLscnt[5]--;
LL5_term();
LL6_sumexpr2();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 11:/* OR_OP */
case 12:/* AND_OP */
case 13:/* CAND_OP */
case 14:/* COR_OP */
case 20:/* COMPARE_OP */
case 26:/* THEN_TOK */
case 28:/* COMMA */
case 29:/* SEMICOLON */
case 36:/* RPARREN */
LLscnt[4]--;
break;
}
}
static void LL7_sumexpr(void){
LLscnt[4]++;
LL5_term();
LL6_sumexpr2();
}
static void LL8_relexpr2(void){
LL_0:
switch (LLcsymb) {
case 20:/* COMPARE_OP */
LLtcnt[20]--;
LLscnt[6]++;
LLtcnt[20]++;
LL_SCANDONE(276);/* COMPARE_OP */
LLread();
LLscnt[6]--;
LL7_sumexpr();
LL8_relexpr2();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 11:/* OR_OP */
case 12:/* AND_OP */
case 13:/* CAND_OP */
case 14:/* COR_OP */
case 26:/* THEN_TOK */
case 28:/* COMMA */
case 29:/* SEMICOLON */
case 36:/* RPARREN */
LLtcnt[20]--;
break;
}
}
static void LL9_relexpr(void){
LL_0:
switch (LLcsymb) {
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 17:/* MIN_OP */
case 23:/* NUMBER */
case 31:/* IDENTIFIER */
case 35:/* LPARREN */
LLscnt[7]--;
LLtcnt[20]++;
LL7_sumexpr();
LL8_relexpr2();
break;
case 25:/* BOOLEAN */
LLscnt[7]--;
LL_SCANDONE(281);/* BOOLEAN */
LLread();
break;
}
}
static void LL10_notexpr(void){
LL_0:
switch (LLcsymb) {
case 32:/* NOT_TOK */
LLscnt[8]--;
LLscnt[8]++;
LL_SCANDONE(288);/* NOT_TOK */
LLread();
LL10_notexpr();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 17:/* MIN_OP */
case 23:/* NUMBER */
case 25:/* BOOLEAN */
case 31:/* IDENTIFIER */
case 35:/* LPARREN */
LLscnt[8]--;
LLscnt[7]++;
LL9_relexpr();
break;
}
}
static void LL11_andexpr2(void){
LL_0:
switch (LLcsymb) {
case 12:/* AND_OP */
LLscnt[9]--;
LLscnt[8]++;
LLscnt[9]++;
LL_SCANDONE(268);/* AND_OP */
LLread();
LL10_notexpr();
LL11_andexpr2();
break;
case 13:/* CAND_OP */
LLscnt[9]--;
LLscnt[8]++;
LLscnt[9]++;
LL_SCANDONE(269);/* CAND_OP */
LLread();
LL10_notexpr();
LL11_andexpr2();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 11:/* OR_OP */
case 14:/* COR_OP */
case 26:/* THEN_TOK */
case 28:/* COMMA */
case 29:/* SEMICOLON */
case 36:/* RPARREN */
LLscnt[9]--;
break;
}
}
static void LL12_andexpr(void){
LLscnt[8]++;
LLscnt[9]++;
LL10_notexpr();
LL11_andexpr2();
}
static void LL13_expr2(void){
LL_0:
switch (LLcsymb) {
case 11:/* OR_OP */
LLscnt[10]--;
LLscnt[11]++;
LLscnt[10]++;
LL_SCANDONE(267);/* OR_OP */
LLread();
LLscnt[11]--;
LL12_andexpr();
LL13_expr2();
break;
case 14:/* COR_OP */
LLscnt[10]--;
LLscnt[11]++;
LLscnt[10]++;
LL_SCANDONE(270);/* COR_OP */
LLread();
LLscnt[11]--;
LL12_andexpr();
LL13_expr2();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 26:/* THEN_TOK */
case 28:/* COMMA */
case 29:/* SEMICOLON */
case 36:/* RPARREN */
LLscnt[10]--;
break;
}
}
static void LL14_expr(void){
LLscnt[10]++;
LL12_andexpr();
LL13_expr2();
}
static void LL15_guardedcommand(void){
LLtcnt[26]++;
LLscnt[12]++;
LL14_expr();
LLtcnt[26]--;
LL_SCANDONE(282);/* THEN_TOK */
LLread();
LLscnt[12]--;
LL31_statementset();
}
static void LL16_guardedcommandset(void){
LLtcnt[30]++;
LL15_guardedcommand();
LL_0:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_0;
LLtcnt[30]--;
break;
case 5:/* DOEND_TOK */
case 7:/* IFEND_TOK */
LLtcnt[30]--;
break;
case 30:/* ALTGUARD */
LLtcnt[30]--;
LLscnt[13]++;
LL_SCANDONE(286);/* ALTGUARD */
LLread();
LLscnt[13]--;
LL15_guardedcommand();
}
}
static void LL17_identifierarray(void){
LLtcnt[28]++;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LL_0:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_0;
LLtcnt[28]--;
break;
case 21:/* TYPE_OP */
case 36:/* RPARREN */
LLtcnt[28]--;
break;
case 28:/* COMMA */
LLtcnt[28]--;
LLscnt[14]++;
LL_SCANDONE(284);/* COMMA */
LLread();
LLscnt[14]--;
LL17_identifierarray();
}
}
static void LL18_functioncall(void){
LLscnt[14]++;
LLtcnt[36]++;
LL_SCANDONE(291);/* LPARREN */
LLread();
LLscnt[14]--;
LL17_identifierarray();
LLtcnt[36]--;
LL_SCANDONE(292);/* RPARREN */
}
static void LL19_assignmentcall(void){
LL_0:
switch (LLcsymb) {
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 15:/* ASSIGNMENT_OP */
LLscnt[15]--;
LLscnt[1]++;
LL_SCANDONE(271);/* ASSIGNMENT_OP */
LLread();
LLscnt[1]--;
LL14_expr();
break;
case 28:/* COMMA */
LLscnt[15]--;
LLtcnt[31]++;
LLscnt[15]++;
LLtcnt[28]++;
LLscnt[1]++;
LL_SCANDONE(284);/* COMMA */
LLread();
LLtcnt[31]--;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LL19_assignmentcall();
LLtcnt[28]--;
LL_SCANDONE(284);/* COMMA */
LLread();
LLscnt[1]--;
LL14_expr();
break;
}
}
static void LL20_dostatement(void){
LLscnt[16]++;
LLtcnt[5]++;
LL_SCANDONE(260);/* DOBEGIN_TOK */
LLread();
LLscnt[16]--;
LL16_guardedcommandset();
LLtcnt[5]--;
LL_SCANDONE(261);/* DOEND_TOK */
}
static void LL21_ifstatement(void){
LLscnt[16]++;
LLtcnt[7]++;
LL_SCANDONE(262);/* IFBEGIN_TOK */
LLread();
LLscnt[16]--;
LL16_guardedcommandset();
LLtcnt[7]--;
LL_SCANDONE(263);/* IFEND_TOK */
}
static void LL22_printable(void){
LL_0:
switch (LLcsymb) {
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 24:/* STRING */
LLscnt[17]--;
LL_SCANDONE(280);/* STRING */
LLread();
break;
case 17:/* MIN_OP */
case 23:/* NUMBER */
case 25:/* BOOLEAN */
case 31:/* IDENTIFIER */
case 32:/* NOT_TOK */
case 35:/* LPARREN */
LLscnt[17]--;
LL14_expr();
break;
}
}
static void LL23_printcall(void){
LLscnt[17]++;
LLtcnt[28]++;
LL_SCANDONE(265);/* PRINT_TOK */
LLread();
LL22_printable();
for (;;) {
LL_0:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_0;
break;
case 29:/* SEMICOLON */
break;
case 28:/* COMMA */
LLscnt[17]++;
LL_SCANDONE(284);/* COMMA */
LLread();
LL22_printable();
continue;
}
LLtcnt[28]--;
break;
}
}
static void LL24_readcall(void){
LLtcnt[31]++;
LLtcnt[28]++;
LL_SCANDONE(266);/* READ_TOK */
LLread();
LLtcnt[31]--;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
for (;;) {
LL_0:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_0;
break;
case 29:/* SEMICOLON */
break;
case 28:/* COMMA */
LLtcnt[31]++;
LL_SCANDONE(284);/* COMMA */
LLread();
LLtcnt[31]--;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
continue;
}
LLtcnt[28]--;
break;
}
}
static void LL25_call(void){
LL_0:
switch (LLcsymb) {
case 35:/* LPARREN */
LLscnt[15]--;
LL18_functioncall();
LLread();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 15:/* ASSIGNMENT_OP */
case 28:/* COMMA */
LLscnt[15]--;
LLscnt[15]++;
LL19_assignmentcall();
break;
}
}
static void LL26_declaration(void){
LLscnt[14]++;
LLtcnt[21]++;
LLtcnt[33]++;
LL_SCANDONE(278);/* VAR_TOK */
LLread();
LLscnt[14]--;
LL17_identifierarray();
LLtcnt[21]--;
LL_SCANDONE(277);/* TYPE_OP */
LLread();
LLtcnt[33]--;
LL_SCANDONE(289);/* TYPE */
}
static void LL27_statement(void){
LL_0:
switch (LLcsymb) {
case 22:/* VAR_TOK */
LLscnt[18]--;
LL26_declaration();
LLread();
break;
case 31:/* IDENTIFIER */
LLscnt[18]--;
LLscnt[15]++;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LL25_call();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 9:/* PRINT_TOK */
LLscnt[18]--;
LL23_printcall();
break;
case 10:/* READ_TOK */
LLscnt[18]--;
LL24_readcall();
break;
case 4:/* DOBEGIN_TOK */
LLscnt[18]--;
LL20_dostatement();
LLread();
break;
case 6:/* IFBEGIN_TOK */
LLscnt[18]--;
LL21_ifstatement();
LLread();
break;
}
}
static void LL28_parameterset(void){
LLtcnt[21]++;
LLtcnt[33]++;
LL17_identifierarray();
LLtcnt[21]--;
LL_SCANDONE(277);/* TYPE_OP */
LLread();
LLtcnt[33]--;
LL_SCANDONE(289);/* TYPE */
}
static void LL29_variable(void){
LL_0:
switch (LLcsymb) {
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 25:/* BOOLEAN */
LLscnt[19]--;
LL_SCANDONE(281);/* BOOLEAN */
break;
case 23:/* NUMBER */
LLscnt[19]--;
LL_SCANDONE(279);/* NUMBER */
break;
case 24:/* STRING */
LLscnt[19]--;
LL_SCANDONE(280);/* STRING */
break;
}
}
static void LL30_statementsetV2(void){
LL_0:
switch (LLcsymb) {
case 4:/* DOBEGIN_TOK */
case 6:/* IFBEGIN_TOK */
case 9:/* PRINT_TOK */
case 10:/* READ_TOK */
case 22:/* VAR_TOK */
case 31:/* IDENTIFIER */
LLscnt[12]--;
LLscnt[18]++;
LLtcnt[29]++;
LLscnt[12]++;
LL27_statement();
LLtcnt[29]--;
LL_SCANDONE(285);/* SEMICOLON */
LLread();
LLscnt[12]--;
LL31_statementset();
break;
default:
if (LLskip())
goto LL_0;
/*FALLTHROUGH*/
case 2:/* END_TOK */
case 5:/* DOEND_TOK */
case 7:/* IFEND_TOK */
case 30:/* ALTGUARD */
LLscnt[12]--;
break;
}
}
static void LL31_statementset(void){
LLscnt[12]++;
LL30_statementsetV2();
}
static void LL32_function(void){
LLtcnt[31]++;
LLtcnt[35]++;
LLtcnt[31]++;
LLtcnt[36]++;
LLtcnt[26]++;
LLtcnt[33]++;
LLtcnt[29]++;
LLscnt[12]++;
LLtcnt[2]++;
LLtcnt[29]++;
LL_SCANDONE(264);/* FUNCTION_TOK */
LLread();
LLtcnt[31]--;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LLtcnt[35]--;
LL_SCANDONE(291);/* LPARREN */
LLread();
LL_0:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_0;
LLtcnt[31]--;
break;
case 36:/* RPARREN */
LLtcnt[31]--;
break;
case 31:/* IDENTIFIER */
LLtcnt[31]--;
LL28_parameterset();
LLread();
}
LLtcnt[36]--;
LL_SCANDONE(292);/* RPARREN */
LLread();
LLtcnt[26]--;
LL_SCANDONE(282);/* THEN_TOK */
LLread();
LLtcnt[33]--;
LL_SCANDONE(289);/* TYPE */
LLread();
LLtcnt[29]--;
LL_SCANDONE(285);/* SEMICOLON */
LLread();
LLscnt[12]--;
LL31_statementset();
LLtcnt[2]--;
LL_SCANDONE(258);/* END_TOK */
LLread();
LLtcnt[29]--;
LL_SCANDONE(285);/* SEMICOLON */
}
static void LL33_procedure(void){
LLtcnt[31]++;
LLtcnt[35]++;
LLtcnt[22]++;
LLtcnt[31]++;
LLtcnt[36]++;
LLtcnt[29]++;
LLscnt[12]++;
LLtcnt[2]++;
LLtcnt[29]++;
LL_SCANDONE(293);/* PROCEDURE_TOK */
LLread();
LLtcnt[31]--;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LLtcnt[35]--;
LL_SCANDONE(291);/* LPARREN */
LLread();
LLtcnt[22]--;
LL_SCANDONE(278);/* VAR_TOK */
LLread();
LL_0:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_0;
LLtcnt[31]--;
break;
case 36:/* RPARREN */
LLtcnt[31]--;
break;
case 31:/* IDENTIFIER */
LLtcnt[31]--;
LL28_parameterset();
LLread();
}
LLtcnt[36]--;
LL_SCANDONE(292);/* RPARREN */
LLread();
LLtcnt[29]--;
LL_SCANDONE(285);/* SEMICOLON */
LLread();
LLscnt[12]--;
LL31_statementset();
LLtcnt[2]--;
LL_SCANDONE(258);/* END_TOK */
LLread();
LLtcnt[29]--;
LL_SCANDONE(285);/* SEMICOLON */
}
static void LL34_constant_def(void){
LLtcnt[31]++;
LLtcnt[21]++;
LLtcnt[33]++;
LLtcnt[20]++;
LLscnt[19]++;
LLtcnt[29]++;
LL_SCANDONE(283);/* CONSTANT_TOK */
LLread();
LLtcnt[31]--;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LLtcnt[21]--;
LL_SCANDONE(277);/* TYPE_OP */
LLread();
LLtcnt[33]--;
LL_SCANDONE(289);/* TYPE */
LLread();
LLtcnt[20]--;
LL_SCANDONE(276);/* COMPARE_OP */
LLread();
LL29_variable();
LLread();
LLtcnt[29]--;
LL_SCANDONE(285);/* SEMICOLON */
}
static void LL35_programbody(void){
LLtcnt[27]++;
LLtcnt[37]++;
LLtcnt[8]++;
LLtcnt[1]++;
LLscnt[12]++;
LLtcnt[2]++;
for (;;) {
LL_0:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_0;
break;
case 1:/* BEGIN_TOK */
case 8:/* FUNCTION_TOK */
case 37:/* PROCEDURE_TOK */
break;
case 27:/* CONSTANT_TOK */
LL34_constant_def();
LLread();
continue;
}
LLtcnt[27]--;
break;
}
for (;;) {
LL_1:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_1;
break;
case 1:/* BEGIN_TOK */
case 8:/* FUNCTION_TOK */
break;
case 37:/* PROCEDURE_TOK */
LL33_procedure();
LLread();
continue;
}
LLtcnt[37]--;
break;
}
for (;;) {
LL_2:
switch (LLcsymb) {
default:
if (LLskip()) goto LL_2;
break;
case 1:/* BEGIN_TOK */
break;
case 8:/* FUNCTION_TOK */
LL32_function();
LLread();
continue;
}
LLtcnt[8]--;
break;
}
LLtcnt[1]--;
LL_SCANDONE(257);/* BEGIN_TOK */
LLread();
LLscnt[12]--;
LL31_statementset();
LLtcnt[2]--;
LL_SCANDONE(258);/* END_TOK */
}
static void LL36_header(void){
LLtcnt[31]++;
LLtcnt[29]++;
LL_SCANDONE(259);/* PROGRAM_TOK */
LLread();
LLtcnt[31]--;
LL_SCANDONE(287);/* IDENTIFIER */
LLread();
LLtcnt[29]--;
LL_SCANDONE(285);/* SEMICOLON */
}
static void LL37_start(void){
LLscnt[20]++;
LLtcnt[34]++;
LL36_header();
LLread();
LLscnt[20]--;
LL35_programbody();
LLread();
LLtcnt[34]--;
LL_SCANDONE(290);/* DOT */
}
void parser(void) {
	memset(LLscnt, 0, LL_NSETS * sizeof(int));
	memset(LLtcnt, 0, LL_NTERMINALS * sizeof(int));
	LLtcnt[0]++;
	LLsymb = 0;
	LLreissue = -2 /* LL_NEW_TOKEN */;
	LLread();
	LL37_start();
	LLread();
	if (LLcsymb != 0) LLerror(256 /* EOFILE*/);
}

