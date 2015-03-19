%start parser, start;
%token BEGIN_TOK, END_TOK, PROGRAM_TOK, DOBEGIN_TOK, DOEND_TOK, IFBEGIN_TOK, IFEND_TOK, FUNCTION_TOK, PRINT_TOK, READ_TOK, OR_OP, AND_OP, CAND_OP, COR_OP, ASSIGNMENT_OP, PLUS_OP, MIN_OP, MUL_OP, POW_OP, COMPARE_OP, TYPE_OP, VAR_TOK, NUMBER,STRING, BOOLEAN, THEN_TOK, CONSTANT_TOK, COMMA, SEMICOLON, ALTGUARD, IDENTIFIER, NOT_TOK, TYPE, DOT, LPARREN, RPARREN, PROCEDURE_TOK;
%options "generate-symbol-table generate-lexer-wrapper";
%lexical yylex;

{
/* BEGIN C FILE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symboltable.h"

#include "tree.h"

/* different typechecking errors */
#define DUPLICATE 256
#define WRONGTYPE 257

extern FILE * yyin;
extern char * yytext;

char **lines;
char * file_name;
int linesread;

/* to keep track of errors */
int columnnr;
int linecount;

/* the parse tree */
char *programname;
char *lastidentifier;

/* temporary storage for identifier names */
char *lastidentifier;

void readFile(char *filename) {
	FILE * fin = fopen(filename, "r");
	linesread = 0;
	size_t len = 0;
	ssize_t read = 0;
	/* TODO: remove hardcoded limit */
	lines = calloc(1000, sizeof(char*)); /* calloc, prevents unconditional jumps */
	int guard = getline( &(lines[linesread]), &len, fin);
	while ( guard != -1 ) {
		linesread++;
		guard = getline( &(lines[linesread]), &len, fin);
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

/* debug function used for cleaning up temporary variables */
void utilCleanUp() {
	if (programname != NULL) {
		free(programname);
	}
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
	utilCleanUp();
	freeLines();
	freeSymbolTable();
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
	utilCleanUp();
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);
}


void printTypeError(char *identifier, int ErrorType) {
	int i = 0, k;
	printf("\n");
	k = printf("Error on line %d: ", linecount+1);
	printf("%s", lines[linecount]);
	for (i; i < columnnr + k; i++) {
		printf(" ");
	}
	printf("^\n");
	switch (ErrorType) {
		case DUPLICATE: printf("Duplicate identifier (%s) detected at column %d\n", identifier, columnnr+1);
	}
	
	free(identifier);
	
	utilCleanUp();
	
	freeLines();
	freeSymbolTable();
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	linecount = 0, columnnr = 0;
	programname = NULL;
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
	
	initSymbolTable();
	
	parser();
	
	printf("Program Name: %s\n", programname);
	
	printf("\nSymbolTable:\n");
	printSymbolTable();
	printf("\n");
	/* test region for symbol table */
	
	free(programname);
	
	/* end test region for symbol table */

	if (argc == 2) {
		fclose(yyin);
		yyin = NULL;
	}

	printf("Parsing succesfull\n");
	
	freeSymbolTable();
	freeLines();
	
	return EXIT_SUCCESS;
}

/* EOF c FILE */
}

rootexpr	: LPARREN expr RPARREN
			| IDENTIFIER functioncall?
			| NUMBER
			;


powbase	: MIN_OP powbase
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

notexpr	: NOT_TOK notexpr
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

guardedcommand	: expr THEN_TOK statementset
				;

guardedcommandset	: guardedcommand [ALTGUARD guardedcommand]*
					;

identifierarray	: IDENTIFIER {lastidentifier = strdup(yytext); /* TODO: add a list USE LEXEME IN SCANNER if yytext fails! */  } [COMMA identifierarray]?
				;

functioncall	: LPARREN identifierarray RPARREN
				;

/* original version of assignmentcall that has an equal length for the identifiers and the following expressions (could make semantics very hard to handle) */
assignmentcallV1	: ASSIGNMENT_OP expr
					| COMMA IDENTIFIER assignmentcall COMMA expr
					;

/* newer version of assignmentcall that doesn't make sure yet that the amount of identifers equals the amount of expressions (semantically easier to evaluate) */
assignmentcallV2	: [COMMA IDENTIFIER]* ASSIGNMENT_OP expr [COMMA expr]*
					;

/* select assignmentcall V1 or V2 */
assignmentcall	: assignmentcallV2
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

declaration : VAR_TOK identifierarray TYPE_OP TYPE {
	/* check if the  identifier exists already */
	if (!existsInTop(lastidentifier)) {
		insertIdentifier(lastidentifier, VARIABLE, stringToEvalType(yytext), NULL);
	} else {
		printTypeError(lastidentifier, DUPLICATE);
	}
	
	
	}
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

statementsetV1	: statement statementset2
				| /* epsilon */
				;

/* alternative where every line needs to end with a semicolon */
statementsetV2	: statement SEMICOLON statementset
				| /* epsilon */
				;

/* select statementset V1 or V2 */
statementset	: statementsetV1
				;

function	: FUNCTION_TOK IDENTIFIER LPARREN parameterset? RPARREN THEN_TOK TYPE SEMICOLON statementset END_TOK SEMICOLON
			;

procedure	: PROCEDURE_TOK IDENTIFIER LPARREN VAR_TOK parameterset? RPARREN SEMICOLON statementset END_TOK SEMICOLON
			;

constant_def	: CONSTANT_TOK IDENTIFIER TYPE_OP TYPE COMPARE_OP variable SEMICOLON
				;

/* first procuders then functions? */
programbody : constant_def* [declaration SEMICOLON]* procedure* function* BEGIN_TOK {putBlock(); /* add a new frame of reference */} statementset END_TOK {/* popBlock(); TODO: activate this after degbugging */}
			;
			
header		: PROGRAM_TOK  IDENTIFIER {programname = strdup(yytext); /* the token is freeed in freeNode (normaly) */} SEMICOLON 
			;

start		: header programbody DOT
			; 
