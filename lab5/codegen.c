#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"
#include "expressiontree.h"
#include "tree.h"
#include "symboltable.h"
#include "structarrays.h"

// TODO: statements on the same line must first be evaluated to temp vars
// before asigning them.
// Make Printinteger return a string OR(!) print each argument on it's own line.
// ie println a, b should return:
// a
// b
// Functions, function calls and what have you. Don't mention the pointers!
// Make CAND, AND, COR and COR all conditional (everything is evalled now)

FILE *outputfile;

int varcnt = 0;
int lblcnt = 0;
int indentDept = 0;
Params paramsByRef;

void compileStatement(Stmnt statement);
void compileDo(Do dostatement);
void compileIf(If ifstatement);
void compileExpression(ExpTree exp);

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
			return "int ";
		case INTEGER_TYPE:
			return "Integer ";
		case CONST_INTEGER_TYPE:
			return "const Integer ";
		case REF_INTEGER_TYPE:
			return "Integer ";
		default:
			return "void ";
	}
}

void writeHeaders() {
	WTF("#include <stdio.h>\n");
	WTF("#include <stdlib.h>\n");
	// Use this, to prevent errors
	WTF("#include \"bigints.h\"\n\n");
}

void writeTempVar(int num) {
	WTF("_t");
	char numstring[32];
	sprintf(numstring, "%d", num);
	WTF(numstring);
}

void writeVar(char *name) {
	WTF("*");
	WTF(name);
}

void writeVarRef(char *name) {
	WTF(name);
}

void writeLabel(int num) {
	WTF("lbl");
	char labelstring[32];
	sprintf(labelstring, "%d", num);
	WTF(labelstring);
	WTF(":;\n");
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

void compileIntegerExp(Int intval) {
	int tempvar = varcnt++;
	writeIndents();
	WTF("Integer ");
	writeTempVar(tempvar);
	WTF(";\n");
	writeIndents();
	char *num;
	WTF("makeIntegerFromString(&");
	writeTempVar(tempvar);
	WTF(", \"");
	WTF(intval->value);
	WTF("\");\n");
}

void compileIDexp(ID id) {
	if ((id->type / 10) * 10 == INTEGER_TYPE) {
		writeIndents();
		int tempvar = varcnt++;
		WTF("Integer ");
		writeTempVar(tempvar);
		char *num;
		num = malloc((strlen(id->name) + 42) * sizeof (char));
		sprintf(num, " = %s;\n", id->name);
		WTF(num);
		free(num);
	} else {
		// Boolean type
		writeIndents();
		int tempvar = varcnt++;
		WTF("int ");
		writeTempVar(tempvar);
		char *num;
		num = malloc((strlen(id->name) + 42) * sizeof (char));
		sprintf(num, " = %s;\n", id->name);
		WTF(num);
		free(num);
	}
}

void compileBoolExp(Bool boolval) {
	int tempvar = varcnt++;
	writeIndents();
	WTF("int ");
	writeTempVar(tempvar);
	char num[42];
	if (boolval->value == true) {
		sprintf(num, " = %d;\n", 1);
	} else {
		sprintf(num, " = %d;\n", 0);
	}
	WTF(num);
}

void compilefuncexp(FuncCall funccall) {
	varcnt++;
}

void compilebinodeexp(Bnode bnode) {
	if (bnode->operator == powop) {
		compileExpression(bnode->r);
		int powervar = varcnt - 1;
		compileExpression(bnode->l);
		int basevar = varcnt - 1;
		writeIndents();
		WTF("powInteger(&");
		writeTempVar(basevar);
		WTF(",");
		writeTempVar(powervar);
		WTF(");\n");
	} else if (bnode->operator == plusop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		writeIndents();
		WTF("addInteger(&");
		writeTempVar(left);
		WTF(",");
		writeTempVar(right);
		WTF(");\n");
	} else if (bnode->operator == minop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		writeIndents();
		WTF("subInteger(&");
		writeTempVar(left);
		WTF(",");
		writeTempVar(right);
		WTF(");\n");
	} else if (bnode->operator == mulop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		writeIndents();
		WTF("mulInteger(&");
		writeTempVar(left);
		WTF(",");
		writeTempVar(right);
		WTF(");\n");
	} else if (bnode->operator == divop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		writeIndents();
		WTF("divInteger(&");
		writeTempVar(left);
		WTF(",");
		writeTempVar(right);
		WTF(");\n");
	} else if (bnode->operator == modop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		writeIndents();
		WTF("modInteger(&");
		writeTempVar(left);
		WTF(",");
		writeTempVar(right);
		WTF(");\n");
	} else if (bnode->operator == andop || bnode->operator == candop) {
		// CAND and AND will behave exactly the same
		char num[64];
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int falselabel = lblcnt++;
		writeIndents();
		WTF("if (");
		writeTempVar(left);
		WTF(" == 0) {\n");
		indentDept++;
		writeIndents();
		writeGoto(falselabel);
		indentDept--;
		writeIndents();
		WTF("}\n");
		compileExpression(bnode->r);
		int right = varcnt - 1;
		writeIndents();
		writeTempVar(left);
		WTF(" = ");
		writeTempVar(left);
		WTF(" && ");
		writeTempVar(right);
		WTF(";\n");
		writeIndents();
		writeLabel(falselabel);
		int answer = varcnt++;
		writeIndents();
		WTF("int ");
		writeTempVar(answer);
		WTF(" = ");
		writeTempVar(left);
		WTF(";\n");
	} else if (bnode->operator == corop || bnode->operator == orop) {
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int truelabel = lblcnt++;
		writeIndents();
		WTF("if (");
		writeTempVar(left);
		WTF(") {\n");
		indentDept++;
		writeIndents();
		writeGoto(truelabel);
		indentDept--;
		writeIndents();
		WTF("}\n");
		compileExpression(bnode->r);
		int right = varcnt - 1;
		writeIndents();
		writeTempVar(left);
		WTF(" = ");
		writeTempVar(left);
		WTF(" || ");
		writeTempVar(right);
		WTF(";\n");
		writeIndents();
		writeLabel(truelabel);
		int answer = varcnt++;
		writeIndents();
		WTF("int ");
		writeTempVar(answer);
		WTF(" = ");
		writeTempVar(left);
		WTF(";\n");
	} else if (bnode->operator == gtop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int tempvar = varcnt++;
		int answer = varcnt++;
		
		writeIndents();
		WTF("int ");
		writeTempVar(tempvar);
		WTF(" = compareTo(");
		writeTempVar(left);
		WTF(", ");
		writeTempVar(right);
		WTF(");\n");
		writeIndents();
		WTF("int ");
		writeTempVar(answer);
		WTF(" = ");
		writeTempVar(tempvar);
		WTF(" == 1;\n");
	} else if (bnode->operator == ltop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int tempvar = varcnt++;
		int answer = varcnt++;
		
		writeIndents();
		WTF("int ");
		writeTempVar(tempvar);
		WTF(" = compareTo(");
		writeTempVar(left);
		WTF(", ");
		writeTempVar(right);
		WTF(");\n");
		writeIndents();
		WTF("int ");
		writeTempVar(answer);
		WTF(" = ");
		writeTempVar(tempvar);
		WTF(" == -1;\n");
		
	} else if (bnode->operator == geop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int tempvar = varcnt++;
		int answer = varcnt++;
		
		writeIndents();
		WTF("int ");
		writeTempVar(tempvar);
		WTF(" = compareTo(");
		writeTempVar(left);
		WTF(", ");
		writeTempVar(right);
		WTF(");\n");
		writeIndents();
		WTF("int ");
		writeTempVar(answer);
		WTF(" = ");
		writeTempVar(tempvar);
		WTF(" >= 0;\n");
		
	} else if (bnode->operator == leop) {
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int tempvar = varcnt++;
		int answer = varcnt++;
		
		writeIndents();
		WTF("int ");
		writeTempVar(tempvar);
		WTF(" = compareTo(");
		writeTempVar(left);
		WTF(", ");
		writeTempVar(right);
		WTF(");\n");
		writeIndents();
		WTF("int ");
		writeTempVar(answer);
		WTF(" = ");
		writeTempVar(tempvar);
		WTF(" <= 0;\n");
		
	} else if ((getExpType(bnode->l) * 10) / 10 == INTEGER_TYPE) {
		// EQ en NEQ For integers
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int tempvar = varcnt++;
		int answer = varcnt++;
		
		writeIndents();
		WTF("int ");
		writeTempVar(tempvar);
		WTF(" = compareTo(");
		writeTempVar(left);
		WTF(",");
		writeTempVar(right);
		WTF(");\n");
		if (bnode->operator == eqop) {
			writeIndents();
			WTF("int ");
			writeTempVar(answer);
			WTF(" = ");
			writeTempVar(tempvar);
			WTF(" == 0);\n");
		} else {
			// NEQ op
			writeIndents();
			WTF("int ");
			writeTempVar(answer);
			WTF(" = ");
			writeTempVar(tempvar);
			WTF(" != 0);\n");
		}
	} else {
		// EQ en NEQ For booleans
		compileExpression(bnode->r);
		int right = varcnt - 1;
		compileExpression(bnode->l);
		int left = varcnt - 1;
		int answer = varcnt++;
		char num[64];
		if (bnode->operator == eqop) {
			writeIndents();
			WTF("int ");
			writeTempVar(answer);
			WTF(" = ");
			writeTempVar(left);
			WTF(" == ");
			writeTempVar(right);
			WTF(";\n");
		} else {
			// NEQ op
						writeIndents();
			WTF("int ");
			writeTempVar(answer);
			WTF(" = ");
			writeTempVar(left);
			WTF(" != ");
			writeTempVar(right);
			WTF(";\n");
		}
	}
}

void compileunodeexp(Unode unode) {
	compileExpression(unode->e);
	int expvar = varcnt - 1;
	if (unode->operator == notop) {
		int newvar = varcnt++;
		writeIndents();
		WTF("int ");
		writeTempVar(newvar);
		WTF(" = !");
		writeTempVar(expvar);
		WTF(";\n");
	} else if (unode->operator == negop) {
		int newvar = varcnt++;
		writeIndents();
		WTF("Integer ");
		writeTempVar(newvar);
		WTF(";\n");
		writeIndents();
		WTF("makeIntegerFromString(&");
		writeTempVar(newvar);
		WTF(",\"0\");\n");
		writeIndents();
		WTF("subInteger(&");
		writeTempVar(newvar);
		WTF(", ");
		writeTempVar(expvar);
		WTF(");\n");
	} else {
		printf("ERRORZZZ....\n");
	}
}

void compileExpression(ExpTree exp) {
	switch (exp->kind) {
		case unodeexp:
			compileunodeexp(exp->node.unode);
			break;
		case bnodeexp:
			compilebinodeexp(exp->node.bnode);
			break;
		case idexp:
			compileIDexp(exp->node.id);
			break;
		case funcexp:
			compilefuncexp(exp->node.funcCall);
			break;
		case intexp:
			compileIntegerExp(exp->node.intval);
			break;
		case boolexp:
			compileBoolExp(exp->node.boolval);
			break;
		default:
			printf("Unkown expression kind...\n");
			//SHOULD NOT HAPPEN
	}

	//WTF("//compile the expression here\n");
	//WTF("Integer t0;\nmakeIntegerFromString(&t0, \"1\");//dummy\n");
	//varcnt++;
	//TODO
}

void compileAss(Ass assignment) {
	compileExpression(assignment->expTree);
	writeIndents();
	writeVar(assignment->id->name);
	WTF(" = ");
	writeTempVar(varcnt - 1);
	WTF(";\n");
}

void compileDec(Dec declaration) {
	writeIndents();
	WTF(getCTypeString((declaration->id->type / 10)*10));
	writeVar(declaration->id->name);
	if (indentDept > 0) {
		WTF(" = malloc(sizeof ( ");
		WTF(getCTypeString((declaration->id->type / 10)*10));
		WTF("))");
	}
	WTF(";\n");
}

void writeGlobalDecMalloc(Dec declaration) {
	writeIndents();
	writeVarRef(declaration->id->name);
	WTF(" = malloc(sizeof ( ");
	WTF(getCTypeString((declaration->id->type / 10)*10));
	WTF("));\n");
}

void writeConstantInitialization(Dec declaration) {
	compileExpression(declaration->expTree);
	writeIndents();
	writeVar(declaration->id->name);
	WTF(" = ");
	writeTempVar(varcnt - 1);
	WTF(";\n");
}

void compileDo(Do dostatement) {
	writeIndents();
	WTF("/* START DO */\n");
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
	sprintf(num, "[%d] = {0}; //True array\n", dostatement->numGCommands);
	WTF(num);

	/* initialize random var */
	int randomvar = varcnt++;
	writeIndents();
	WTF("int ");
	writeTempVar(randomvar);
	WTF(" = -1; // Random Var\n");

	int startlabel = lblcnt++;
	int enddolabel = lblcnt++;
	writeIndents();
	writeLabel(startlabel);

	// First evaluate everything
	for (int i = 0; i < dostatement->numGCommands; i++) {
		GCommand g = dostatement->gCommands[i];
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
		indentDept--;
		writeIndents();
		WTF("}\n");
		indentDept--;
		writeIndents();
		WTF("} else {\n");
		indentDept++;
		// Set this one in the truth table to false;
		writeIndents();
		writeTempVar(arrayloc);
		sprintf(num, "[%d] = 0;\n", i);
		WTF(num);
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
	// End of Do loop
	writeIndents();
	writeGoto(enddolabel);
	indentDept--;
	writeIndents();
	WTF("}\n");

	// Reset truecounter
	writeIndents();
	writeTempVar(truecounter);
	WTF(" = 0; //Reset True counter\n");

	// Then determine which to exucute
	int startwhilelabel = lblcnt++;
	writeIndents();
	writeLabel(startwhilelabel);
	writeIndents();
	writeTempVar(randomvar);
	sprintf(num, " = rand() %% %d;\n", dostatement->numGCommands);
	WTF(num);
	// Check if this one is true
	writeIndents();
	WTF("if (");
	writeTempVar(arrayloc);
	sprintf(num, "[t%d] != 1) {\n", randomvar);
	WTF(num);
	indentDept++;
	writeIndents();
	writeGoto(startwhilelabel);
	indentDept--;
	writeIndents();
	WTF("}\n");
	writeIndents();
	//Jump back to start
	writeGoto(startlabel);
	writeIndents();
	writeLabel(enddolabel);
	writeIndents();
	WTF("/* END DO */\n");
	// DONE
}

void compileIf(If ifstatement) {
	writeIndents();
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

void compileParameter(Param parameter) {
	WTF(getCTypeString(parameter->id->type));
	WTF(parameter->id->name);
	if (parameter->call == byRef) {
		paramsByRef->numParams++;
		if (paramsByRef->numParams == 1) {
			paramsByRef->params = malloc(paramsByRef->numParams * sizeof (Param));
		} else {
			paramsByRef->params = realloc(paramsByRef->params, paramsByRef->numParams * sizeof (Param));
		}
		paramsByRef->params[paramsByRef->numParams - 1] = parameter;
	}
}

void compileFunc(FuncDef function) {
	WTF(getCTypeString(function->id->type));
	WTF(function->id->name);
	WTF("(");
	paramsByRef = malloc(sizeof (struct Params));
	paramsByRef->numParams = 0;
	for (int i = 0; i < function->numParams; i++) {
		if (i != 0) WTF(", ");
		compileParameter(function->params[i]);
	}
	WTF(") {\n");
	indentDept++;
	for (int i = 0; i < function->numStmnts; i++) {
		compileStatement(function->stmnts[i]);
	}
	// TODO print for return statement
	indentDept--;
	WTF("}\n");
	if (paramsByRef->numParams > 0) {
		free(paramsByRef->params);
	}
	free(paramsByRef);
}

void compileProc(ProcDef procedure) {
	WTF("void ");
	WTF(procedure->name);
	WTF("(");
	paramsByRef = malloc(sizeof (struct Params));
	paramsByRef->numParams = 0;
	for (int i = 0; i < procedure->numParams; i++) {
		if (i != 0) WTF(", ");
		compileParameter(procedure->params[i]);
	}
	WTF(") {\n");
	indentDept++;
	for (int i = 0; i < procedure->numStmnts; i++) {

		compileStatement(procedure->stmnts[i]);
	}
	indentDept--;
	WTF("}\n");
	if (paramsByRef->numParams > 0) {
		free(paramsByRef->params);
	}
	free(paramsByRef);
}

void compileMain(Prog program) {
	WTF("int main(int argc, char **argv){\n");
	indentDept++;
	if (program->numConstDefs > 0) WTF("// constant mallocs, will be init below\n");
	for (int i = 0; i < program->numConstDefs; i++) {
		writeGlobalDecMalloc(program->constDefs[i]);
	}
	if (program->numConstDefs > 0) WTF("\n");
	if (program->numVarDefs > 0) WTF("// varable mallocs\n");
	for (int i = 0; i < program->numVarDefs; i++) {
		writeGlobalDecMalloc(program->varDefs[i]);
	}
	if (program->numVarDefs > 0) WTF("\n");
	if (program->numConstDefs > 0) WTF("// constant initializations\n");
	for (int i = 0; i < program->numConstDefs; i++) {
		writeConstantInitialization(program->constDefs[i]);
	}
	if (program->numConstDefs > 0) WTF("\n");
	if (program->numBodyStmnts > 0) WTF("// main body\n");
	paramsByRef = malloc(sizeof (struct Params));
	paramsByRef->numParams = 0;
	// main doesnt have parameters
	for (int i = 0; i < program->numBodyStmnts; i++) {
		compileStatement(program->bodyStmnts[i]);
	}
	if (paramsByRef->numParams > 0) {
		free(paramsByRef->params);
	}
	free(paramsByRef);
	writeIndents();
	WTF("return EXIT_SUCCESS;\n");
	indentDept--;
	WTF("}\n");
}

void generateCode(Prog program, char *outputfilename) {
	outputfile = fopen(outputfilename, "w");
	writeHeaders();

	if (program->numConstDefs > 0) WTF("// global constant definitions, will be malloced and init once in the main\n");
	for (int i = 0; i < program->numConstDefs; i++) {
		compileDec(program->constDefs[i]);
	}
	if (program->numConstDefs > 0) WTF("\n");
	if (program->numVarDefs > 0) WTF("// global variable definitions, will be malloced in the main\n");
	for (int i = 0; i < program->numVarDefs; i++) {
		compileDec(program->varDefs[i]);
	}
	if (program->numVarDefs > 0) WTF("\n");
	if (program->numProcDefs > 0) WTF("// procedure definitions\n");
	for (int i = 0; i < program->numProcDefs; i++) {
		compileProc(program->procDefs[i]);
		WTF("\n");
	}
	if (program->numFuncDefs > 0) WTF("// function definitions\n");
	for (int i = 0; i < program->numFuncDefs; i++) {
		compileFunc(program->funcDefs[i]);
		WTF("\n");
	}
	compileMain(program);

	fclose(outputfile);
}
