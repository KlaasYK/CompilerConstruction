%start parser, start;
%token BEGIN_TOK, END_TOK, COMMENT, PROGRAM_TOK, DOBEGIN_TOK, DOEND_TOK, IFBEGIN_TOK, IFEND_TOK, FUNCTION_TOK, OR_OP, AND_OP, CAND_OP, COR_OP, ASSIGNMENT_OP, PLUS_OP, MUL_OP, POW_OP, COMPARE_OP, TYPE_OP, VAR_TOK, VARIABLE, NUMBER,STRING, BOOLEAN, THEN_TOK, CONSTANT_TOK, COMMA, SEMICOLON, ALTGUARD, FUNCNAME, PROGRAMNAME, IDENTIFIER, NOT_TOK, TYPE, EOL, ERROR, DOT, LPARREN, RPARREN, PROCEDURE_TOK, WHITESPACE;
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
}


start		: header programbody
			; 

header		: PROGRAM_TOK IDENTIFIER SEMICOLON 
			;

programbody : BEGIN_TOK functioncall END_TOK DOT
			;
			
functioncall	: IDENTIFIER STRING SEMICOLON
				;


