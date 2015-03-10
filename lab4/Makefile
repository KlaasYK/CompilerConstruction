ifeq ($(OS),Windows_NT)
	EXE = gclc.exe
else
	EXE = gclc
endif

GCL = $(subst .gcl,.c99,$(wildcard *.gcl))


all: parser scanner
	gcc -o $(EXE) egclgrammar.o lex.yy.o
parser: egclgrammar.g
	LLnextgen egclgrammar.g
	gcc -c egclgrammar.c
scanner: egclscanner.fl
	flex egclscanner.fl
	gcc -c lex.yy.c


run: $(GCL)
	
%.c99: %.gcl $(EXE)
	./$(EXE) $<

clean: 
	rm -f lex.yy.c
	rm -f lex.yy.o
	rm -f egclgrammar.c
	rm -f egclgrammar.h
	rm -f egclgrammar.o
	rm -f gclc
	rm -f gclc.exe