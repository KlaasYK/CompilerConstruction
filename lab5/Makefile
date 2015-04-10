ifeq ($(OS),Windows_NT)
	EXE = gclc.exe
else
	EXE = gclc
endif

GCL2 = $(subst .gcl,.c99,$(wildcard *.gcl))

GCL = riktest2.c99

all: parser scanner cfiles
	gcc -g -o $(EXE) egclgrammar.o lex.yy.o symboltable.o tree.o expressiontree.o bigints.o codegen.o
parser: egclgrammar.g
	LLnextgen egclgrammar.g
scanner: egclscanner.fl
	flex egclscanner.fl
cfiles: egclgrammar.c lex.yy.c symboltable.c bigints.c
	gcc -c -g -std=gnu99 egclgrammar.c lex.yy.c symboltable.c expressiontree.c tree.c bigints.c codegen.c


run: $(GCL)
	
%.c99: %.gcl $(EXE)
	./$(EXE) $<
	gcc -c -g -std=gnu99 out.c99 bigints.c
	gcc -g -o a.out out.o bigints.o

clean: 
	rm -f lex.yy.c
	rm -f lex.yy.o
	rm -f egclgrammar.c
	rm -f egclgrammar.h
	rm -f egclgrammar.o
	rm -f gclc
	rm -f gclc.exe
	rm -f gclc.exe.stackdump
	rm -f symboltable.o
	rm -f tree.o
	rm -f expressiontree.o
	rm -f bigints.o
	rm -f codegen.o
	rm -f out.c99
	rm -f out.o
	rm -f out
	rm -f out.exe