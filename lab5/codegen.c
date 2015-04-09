#include <stdio.h>
#include <stdlib.h>

#include "codegen.h"
#include "tree.h"
#include "symboltable.h"

FILE *outputfile;

int varcnt = 0;
int lblcnt = 0;

void WTF(char *code) {
	fputs(code,outputfile);
}

char *getCTypeString(int type) {
	switch(type) {
		case BOOLEAN_TYPE:
		case CONST_BOOLEAN_TYPE:
			return "int";
		case REF_BOOLEAN_TYPE:
			return "int *";
		case INTEGER_TYPE:
		case CONST_INTEGER_TYPE:
			return "Integer";
		case REF_INTEGER_TYPE:
			return "Integer *";
		default:
			return "void";
	}
}

void writeHeaders() {
		WTF("#include <stdio.h>\n");
		WTF("#include <stdlib.h>\n");
		WTF("#include \"bigints.h\"\n");
}


void compileDo() {
	
}

void compileIf() {
	
}

void compileFunc(FuncDef function) {
	WTF(getCTypeString(function->id->type));
	WTF(" ");
	WTF(function->id->name);
	WTF("(");
	// arguments
	WTF(") {\n");
	//body
	WTF("}\n");
}

void compileProc(ProcDef procedure) {
	WTF("void ");
	WTF(procedure->name);
	WTF("(");
	// arguments
	WTF(") {\n");
	//body
	WTF("}\n");
}

void compileMain() {
	WTF("int main(int argc, char **argv){\n");
	
	//TODO: compile body statements
	
	WTF("return EXIT_SUCCESS;\n");
	WTF("}\n");
}

void generateCode(Prog program, char *outputfilename) {
	outputfile = fopen(outputfilename, "w");
	
	writeHeaders();
	
	// TODO: write constants and globals
	
	for (int i = 0; i < program->numProcDefs; i++) {
		compileProc(program->procDefs[i]);
	}
	
	for (int i = 0; i < program->numFuncDefs; i++) {
		compileFunc(program->funcDefs[i]);
	}
	
	compileMain();
	
	fclose(outputfile);
}