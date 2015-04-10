#include <stdio.h>
#include <stdlib.h>

#include "codegen.h"
#include "tree.h"
#include "symboltable.h"

FILE *outputfile;

int varcnt = 0;
int lblcnt = 0;

void compileStatement(Stmnt statement);
void compileDo(Do dostatement);
void compileIf(If ifstatement);

void WTF(char *code) {
	fputs(code,outputfile);
}

char *getCTypeString(int type) {
	switch(type) {
		case BOOLEAN_TYPE:
			return "int";
		case CONST_BOOLEAN_TYPE:
			return "const int";
		case REF_BOOLEAN_TYPE:
			return "int *";
		case INTEGER_TYPE:
			return "Integer";
		case CONST_INTEGER_TYPE:
			return "const Integer *";
		case REF_INTEGER_TYPE:
			return "Integer *";
		default:
			return "void";
	}
}

void writeHeaders() {
		WTF("#include <stdio.h>\n");
		WTF("#include <stdlib.h>\n");
		// Use this, to prevent errors
		WTF("#include <stdint.h>\n");
		WTF("#include \"bigints.h\"\n");
}

void writeLabel(int num) {
		WTF("label lbl");
		
		WTF("");
}

void compileDec(Dec declaration) {
	WTF(getCTypeString(declaration->id->type));
	WTF(" ");
	WTF(declaration->id->name);
	WTF(" = ");
	// TODO: expression tree
	
	WTF(";\n");
}

void compileDo(Do dostatement) {
	// TODO:
}

void compileIf(If ifstatement) {
	
}

void compileWriteCall(WCall write) {
	WTF("printf(\"");
	int k = 0;
	for (int i = 0; i < write->numitems; i++) {
		Printable p = write->items[i];
		if (p->kind == stringKind) {
			WTF(p->string);
		} else {
			k++;
			// TODO
			// make a switch for the kind
			// use printInteger if type is interger (ie start new printf)
			// or make PrintInteger return a string
			// use %d for booleans
		}
	}
	
	//TODO: check if println or print was called.
	// Needs to be stored inside the tree!
	// Make an extra action for this in the grammar!
	WTF("\"");
	// Are there any expressions to be printed?
	if (k > 0) {
		WTF(",");
		for (int i = 0; i < write->numitems; i++) {
			Printable p = write->items[i];
			if (p->kind == stringKind) {
				// DO nothing
			} else {
				// TODO
				// make a switch for the kind
				// use printInteger if type is interger (ie start new printf)
				// or make PrintInteger return a string
				// use %d for booleans
				WTF(",");
			}
		}
	}
	WTF(");\n");
}

void compileStatement(Stmnt statement) {
	switch(statement->kind) {
		case decStmnt: compileDec(statement->dec);break;
		case assStmnt: break; //TODO;
		case funcCallStmnt: break; //TODO:
		case procCallStmnt: break; //TODO;
		case readCallStmnt: break; //TODO;
		case writeCallStmnt: compileWriteCall(statement->wCall); break; //TODO;
		case ifStmnt: break; compileIf(statement->ifStmnt);
		case doStmnt: break; compileDo(statement->doStmnt);
	}
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

void compileMain(Prog program) {
	WTF("int main(int argc, char **argv){\n");
	
	for (int i = 0; i < program->numBodyStmnts; i++) {
		compileStatement(program->bodyStmnts[i]);
	}
	
	WTF("return EXIT_SUCCESS;\n");
	WTF("}\n");
}

void generateCode(Prog program, char *outputfilename) {
	outputfile = fopen(outputfilename, "w");
	
	writeHeaders();
	
	for (int i = 0; i < program->numConstDefs; i++) {
		compileDec(program->constDefs[i]);
	}
	
	for (int i = 0; i < program->numVarDefs; i++) {
		compileDec(program->varDefs[i]);
	}
	
	for (int i = 0; i < program->numProcDefs; i++) {
		compileProc(program->procDefs[i]);
	}
	
	for (int i = 0; i < program->numFuncDefs; i++) {
		compileFunc(program->funcDefs[i]);
	}
	
	compileMain(program);
	
	fclose(outputfile);
}