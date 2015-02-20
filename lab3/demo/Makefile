all: parser scanner
	gcc -o demo grammar.o lex.yy.o
parser: grammar.g
	LLnextgen grammar.g
	gcc -c grammar.c
scanner: scanner.fl
	flex scanner.fl
	gcc -c lex.yy.c


