%start parser, start;
%token BEGIN_TOK, END_TOK, PROGRAM_TOK, DOBEGIN_TOK, DOEND_TOK, IFBEGIN_TOK, IFEND_TOK, FUNCTION_TOK, PRINT_TOK, READ_TOK, OR_OP, AND_OP, CAND_OP, COR_OP, ASSIGNMENT_OP, PLUS_OP, MIN_OP, MUL_OP, POW_OP, COMPARE_OP, TYPE_OP, VAR_TOK, NUMBER,STRING, BOOLEAN, THEN_TOK, CONSTANT_TOK, COMMA, SEMICOLON, ALTGUARD, IDENTIFIER, NOT_TOK, TYPE, DOT, LPARREN, RPARREN, PROCEDURE_TOK;
%options "generate-symbol-table generate-lexer-wrapper";
%lexical yylex;

{
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
	int i = 0, k;
	printf("\n");
	k = printf("Error on line %d: ", linecount+1);
	printf("%s", lines[linecount]);
	for (i; i < columnnr + k; i++) {
		printf(" ");
	}
	printf("^\n");
	switch (token) {
		case LL_MISSINGEOF:
		printf("%s:%d: Expected %s, found %s (%s).\n", file_name, linecount+1, LLgetSymbol(EOFILE), LLgetSymbol(LLsymb), yytext);
		break;
		case LL_DELETE:
		printf("%s:%d: Unexpected %s (%s).\n", file_name, linecount+1, LLgetSymbol(LLsymb), yytext);
		break;
		default:
		printf("%s:%d: Expected %s, found %s (%s).\n", file_name, linecount+1, LLgetSymbol(token), LLgetSymbol(LLsymb), yytext);
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
}

rootexpr	: LPARREN expr RPARREN
			| IDENTIFIER functioncall?
			| NUMBER
			;


powbase	: MIN_OP rootexpr
			| rootexpr
			;

factor2	: POW_OP powbase factor2
		| /* epsilon */
		;

factor	: powbase factor2 
		;

term2	: MUL_OP factor term2
		| /* epsilon */
		;

term	: factor term2
		;

sumexpr2	: PLUS_OP term sumexpr2
			| MIN_OP term sumexpr2
			| /* epsilon */
			;

sumexpr	: term sumexpr2
		;

relexpr2	: COMPARE_OP sumexpr relexpr2
			| /* epsilon */
			;

relexpr : sumexpr relexpr2
		| BOOLEAN
		;

notexpr	: NOT_TOK relexpr
		| relexpr
		;

andexpr2	: AND_OP notexpr andexpr2
			| CAND_OP notexpr andexpr2
			| /* epsilon */
			;

andexpr	: notexpr andexpr2 
		;
			
expr2	: OR_OP andexpr expr2
		| COR_OP andexpr expr2
		| /* epsilon */
		;

expr	: andexpr expr2
		;

/* C-like guard? */
guardedcommand	: expr THEN_TOK statementset
				;

guardedcommandset	: guardedcommand [ALTGUARD guardedcommand]?
					;

identifierarray	: IDENTIFIER [COMMA identifierarray]?
				;

functioncall	: LPARREN identifierarray RPARREN
				;

assignmentcall	: ASSIGNMENT_OP expr
				| COMMA IDENTIFIER assignmentcall COMMA expr
				;

dostatement	:	DOBEGIN_TOK guardedcommandset DOEND_TOK
			;

ifstatement	:	IFBEGIN_TOK guardedcommandset IFEND_TOK
			;

printable	: STRING
			| expr
			;

printcall	: PRINT_TOK printable [COMMA printable]*
			;

readcall	: READ_TOK IDENTIFIER [COMMA IDENTIFIER]*
			;

call	:	functioncall
		|	assignmentcall
		;

declaration : VAR_TOK identifierarray TYPE_OP TYPE
			;

statement	: declaration
			| IDENTIFIER call
			| printcall
			| readcall
			| dostatement
			| ifstatement
			;

parameterset 	: identifierarray TYPE_OP TYPE
				;

variable		: BOOLEAN
				| NUMBER
				| STRING
				;
			
/* can the last statement in a block end with a semicolon? internet says of a certain version of gcl that a statement has the rule: S -> S;S | ...*/
statementset2	: SEMICOLON statementset
				| /* epsilon */
				;

statementset	: statement statementset2
				| /* epsilon */
				;

function	: FUNCTION_TOK IDENTIFIER LPARREN parameterset? RPARREN THEN_TOK TYPE SEMICOLON statementset END_TOK SEMICOLON
			;

procedure	: PROCEDURE_TOK IDENTIFIER LPARREN VAR_TOK parameterset? RPARREN SEMICOLON statementset END_TOK SEMICOLON
			;

constant_def	: CONSTANT_TOK IDENTIFIER TYPE_OP TYPE COMPARE_OP variable SEMICOLON
				;

			/* first procuders then functions? */
programbody : constant_def* procedure* function* BEGIN_TOK statementset END_TOK
			;

header		: PROGRAM_TOK IDENTIFIER SEMICOLON 
			;

start		: header programbody DOT
			; 