#include <stdio.h>
#include <stdlib.h>

#include "codegen.h"
#include "tree.h"
#include "symboltable.h"
#include "structarrays.h"

FILE *outputfile;

int varcnt = 0;
int lblcnt = 0;
int indentDept = 0;
ExpTree *constantExps;

void compileStatement(Stmnt statement);
void compileDo(Do dostatement);
void compileIf(If ifstatement);

void WTF(char *code) {
	fputs(code, outputfile);
}

char *getCTypeString(int type) {
	switch (type) {
		case BOOLEAN_TYPE:
			return "int ";
		case CONST_BOOLEAN_TYPE:
			return "const int ";
		case REF_BOOLEAN_TYPE:
			return "int *";
		case INTEGER_TYPE:
			return "Integer ";
		case CONST_INTEGER_TYPE:
			return "const Integer ";
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
	WTF("#include \"bigints.h\"\n\n");
}

void writeTempVar(int num) {
	WTF("t");
	char numstring[32];
	sprintf(numstring, "%d", num);
	WTF(numstring);
}

void writeLabel(int num) {
	WTF("label lbl");
	char labelstring[32];
	sprintf(labelstring, "%d", num);
	WTF(labelstring);
	WTF(";\n");
}

void writeGoto(int num) {
    WTF("goto lbl");
    char labelstring[32];
    sprintf(labelstring, "%d", num);
    WTF(labelstring);
    WTF(";\n");
}

void writeIndents() {
	for (int i = 0; i < indentDept; i++) {
		WTF("    ");
	}
}

void writeAssignment(char *varName, char *lhs, char op, char *rhs) {
	//TODO
}

void compileExpression(ExpTree exp) {
	WTF("//compile the expression here\n");
	WTF("Integer t0;\nmakeIntegerFromString(&t0, \"1\");//dummy\n");
	varcnt++;
	//TODO
}

void compileAss(Ass assignment) {
	//TODO
}

void compileDec(Dec declaration) {
	writeIndents();
	WTF(getCTypeString((declaration->id->type/10)*10));
	WTF(declaration->id->name);
	WTF(";\n");
	if (declaration->idType == constant) {
		WTF("// constant, will be init once in the main");
	}

}

void compileDo(Do dostatement) {
	// TODO:
}

void compileIf(If ifstatement) {
	WTF("/* START IF */\n");
    int truecounter = varcnt++;
    int arrayloc = varcnt++;
    writeIndents();
	WTF("int ");
    writeTempVar(truecounter);
    WTF(" = 0; //True counter\n");
	writeIndents();
    WTF("int ");
    writeTempVar(arrayloc);
    char num[40];
    sprintf(num, "[%d] = {0}; //True array\n", ifstatement->numGCommands);
    WTF(num);
	
	/* initialize random var */
	int randomvar = varcnt++;
	writeIndents();
	WTF("int ");
	writeTempVar(randomvar);
	WTF(" = -1; // Random Var\n");
	
    int startlabel = lblcnt++;
	int endiflabel = lblcnt++;
	writeIndents();
    writeLabel(startlabel);

    // First evaluate everything
    for (int i = 0; i < ifstatement->numGCommands; i++) {
		GCommand g = ifstatement->gCommands[i];
		compileExpression(g->condition);
		writeIndents();
		WTF("if (");
		writeTempVar(varcnt - 1);
		WTF(" != 0) {\n");
		indentDept++;
		// If this one is true, 
		writeIndents();
		writeTempVar(truecounter);
		WTF("++;\n");
		writeIndents();
		writeTempVar(arrayloc);
		sprintf(num, "[%d] = 1;\n", i);
		WTF(num);
		writeIndents();
		//Check if this one may execute
		WTF("if (");
		writeTempVar(randomvar);
		sprintf(num, "== %d", i);
		WTF(num);
		WTF(") {\n");
		indentDept++;
		// Compile the statements
		for (int j = 0; j < g->numStmnts; j++) {
			compileStatement(g->stmnts[j]);
		}
		writeIndents();
		writeGoto(endiflabel);
		indentDept--;
		writeIndents();
		WTF("}\n");
		indentDept--;
		writeIndents();
		WTF("}\n");
	}
	// Check if atleast one of them is true
	writeIndents();
	WTF("if (");
	writeTempVar(truecounter);
	WTF(" < 1) {\n");
	indentDept++;
	// Error
	writeIndents();
	WTF("printf(\"Runtime Error, no guard is true!\\n\");\n");
	writeIndents();
	WTF("exit(EXIT_FAILURE);\n");
	indentDept--;
	writeIndents();
	WTF("}\n");
	
	// Then determine which to exucute
	int startwhilelabel = lblcnt++;
	writeIndents();
	writeLabel(startwhilelabel);
	writeIndents();
	writeTempVar(randomvar);
	sprintf(num, "= rand() %% %d;\n", ifstatement->numGCommands);
	writeIndents();
	WTF(num);
	// Check if this one is true
	writeIndents();
	WTF("if (");
	writeTempVar(arrayloc);
	sprintf(num, "[t%d] != 1) {\n", randomvar);
	indentDept++;
	writeIndents();
	WTF(num);
	writeIndents();
	writeGoto(startwhilelabel);
	indentDept--;
	writeIndents();
	WTF("}");
	writeIndents();
	//Jump back to start
	writeGoto(startlabel);
	writeIndents();
	writeLabel(endiflabel);
	writeIndents();
	WTF("/* END IF */\n");
	// DONE
}

void compileWriteCall(WCall write) {

	// first compile the expression tree and make a list of temp vars and kinds
	int j = 0;
	int *vars = malloc(write->numitems * sizeof (int));
	ExpKind *kinds = malloc(write->numitems * sizeof (PrintKind));
	for (int i = 0; i < write->numitems; i++) {
		Printable p = write->items[i];
		if (p->kind == expKind) {
			compileExpression(p->exp);
			kinds[j] = getExpType(p->exp);
			vars[j] = varcnt - 1;
			j++;
		}
	}
	// Start printing
	int k = 0;
	writeIndents();
	WTF("printf(\"");
	for (int i = 0; i < write->numitems; i++) {
		Printable p = write->items[i];
		if (p->kind == stringKind) {
			//strip the first and last character (the quotes)
			p->string[strlen(p->string) - 1] = 0;
			WTF(p->string + 1);
		} else {
			if (kinds[k] / 10 == INTEGER_TYPE / 10) {
				WTF("%s");
			} else {
				WTF("%d");
			}
			k++;
		}
	}
	if (write->newLine == true) {
		WTF("\\n");
	}
	WTF("\"");
	// Are there any expressions to be printed?
	for (int i = 0; i < j; i++) {

		WTF(",");
		writeTempVar(vars[i]);
	}
	WTF(");\n");
	free(vars);
	free(kinds);
}

void compileStatement(Stmnt statement) {
    switch (statement->kind) {
	case decStmnt: compileDec(statement->dec);
	    break;
	case assStmnt: compileAss(statement->assignment);
	    break;
	case funcCallStmnt: break; //TODO:
	case procCallStmnt: break; //TODO;
	case readCallStmnt: break; //TODO;
	case writeCallStmnt: compileWriteCall(statement->wCall);
	    break; //TODO
	case ifStmnt: 
	    compileIf(statement->ifStmnt);
		break;
	case doStmnt: 
	    compileDo(statement->doStmnt);
		break;
	default:
		printf("Not Done yet...\n");
    }
}

void compileFunc(FuncDef function) {
	WTF(getCTypeString(function->id->type));
	WTF(" ");
	WTF(function->id->name);
	WTF("(");
	// TODO arguments
	WTF(") {\n");
	indentDept++;
	for (int i = 0; i < function->numStmnts; i++) {

		compileStatement(function->stmnts[i]);
	}
	// TODO print for return statement
	indentDept--;
	WTF("}\n");
}

void compileProc(ProcDef procedure) {
	WTF("void ");
	WTF(procedure->name);
	WTF("(");
	// TODO arguments
	WTF(") {\n");
	indentDept++;
	for (int i = 0; i < procedure->numStmnts; i++) {

		compileStatement(procedure->stmnts[i]);
	}
	indentDept--;
	WTF("}\n");
}

void compileMain(Prog program) {
    WTF("int main(int argc, char **argv){\n");
    indentDept++;
    for (int i = 0; i < program->numBodyStmnts; i++) {
		compileStatement(program->bodyStmnts[i]);
    }
    writeIndents();
    WTF("return EXIT_SUCCESS;\n");
    indentDept--;
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