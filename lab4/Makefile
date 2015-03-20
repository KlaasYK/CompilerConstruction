ifeq ($(OS),Windows_NT)
	EXE = gclc.exe
else
	EXE = gclc
endif

GCL = $(subst .gcl,.c99,$(wildcard *.gcl))


all: parser scanner cfiles tree
	gcc -g -o $(EXE) egclgrammar.o lex.yy.o symboltable.o tree.o expressiontree.o
parser: egclgrammar.g
	LLnextgen egclgrammar.g
scanner: egclscanner.fl
	flex egclscanner.fl
cfiles: egclgrammar.c lex.yy.c symboltable.c
	gcc -c -g -std=c99 egclgrammar.c lex.yy.c symboltable.c
tree: tree.c expressiontree.c
	gcc -c -g -std=c99 expressiontree.c tree.c

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
	rm -f symboltable.o
	rm -f tree.o
	rm -f expressiontree.o