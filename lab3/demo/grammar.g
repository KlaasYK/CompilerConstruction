%start parser, start;
%token LPAR, PLUS, RPAR, ATOK, BTOK;
%options "generate-lexer-wrapper";
%lexical yylex;

{
	#include <stdio.h>
	#include <stdlib.h>

	int main(int argc, char *argv[]) {
		parser();
		printf("Accepted\n");
		return 0;
	}

	void LLmessage(int token) {
		printf("Parse error: %d\n", token);
		exit(EXIT_FAILURE);
	}
}


start :	atom
      | LPAR start PLUS atom RPAR
      ; 

atom : ATOK
     | BTOK
     ;

