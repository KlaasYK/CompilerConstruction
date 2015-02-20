all: parser scanner
	gcc -o gclc egclgrammar.o lex.yy.o
parser: egclgrammar.g
	LLnextgen egclgrammar.g
	gcc -c egclgrammar.c
scanner: egclscanner.fl
	flex egclscanner.fl
	gcc -c lex.yy.c


