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
Params paramsByVal;

int lastline;
int numstatements;
int maxstatements;
int *tempvars;
Ass *stored;

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
	WTF("#include <sys/time.h>\n");
	WTF("#include <string.h>\n");
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
	writeIndents();
	int tempvar = varcnt++;
	if ((id->type / 10) * 10 == INTEGER_TYPE) {
		WTF("Integer ");
	} else {
		// Boolean type
		WTF("int ");
	}
	writeTempVar(tempvar);
	WTF(";\n");
	writeIndents();
	WTF("setInteger(&");
	writeTempVar(tempvar);
	WTF(", ");
	writeVar(id->name);
	WTF(");\n");
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
			WTF(" == 0;\n");
		} else {
			// NEQ op
			writeIndents();
			WTF("int ");
			writeTempVar(answer);
			WTF(" = ");
			writeTempVar(tempvar);
			WTF(" != 0;\n");
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

void halfCompileAss(Ass assignment) {
	compileExpression(assignment->expTree);
	stored[numstatements] = assignment;
	tempvars[numstatements] = varcnt - 1;
	numstatements++;

	//TODO check if numstatements >= maxstatements
}

void compileStoredAss() {
	for (int i = 0; i < numstatements; i++) {
		Ass s = stored[i];
		writeIndents();
		if((s->id->type/10) * 10 == INTEGER_TYPE){
			WTF("setInteger(");
			writeVarRef(s->id->name);
			WTF(", ");
			writeTempVar(tempvars[i]);
			WTF(")");
		}else{
			writeVar(s->id->name);
			WTF(" = ");
			writeTempVar(tempvars[i]);
		}
		WTF(";\n");
		stored[i] = NULL;
		tempvars[i] = -1;
	}
	numstatements = 0;
}

/* not needed anymore, just kept as reference*/
/*void compileAss(Ass assignment) {
	compileExpression(assignment->expTree);
	writeIndents();
	writeVar(assignment->id->name);
	WTF(" = ");
	writeTempVar(varcnt - 1);
	WTF(";\n");
}*/

/* Rick, zijn deze mallocs echt nodig? */
void compileDec(Dec declaration) {
	writeIndents();
	WTF(getCTypeString((declaration->id->type / 10)*10));
	writeVar(declaration->id->name);
	if (indentDept > 0) {
		WTF(" = malloc(sizeof ( ");
		WTF(getCTypeString((declaration->id->type / 10)*10));
		WTF("))");
	}else{
		WTF(" = NULL");
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
	WTF("setInteger(");
	writeVarRef(declaration->id->name);
	WTF(", ");
	writeTempVar(varcnt - 1);
	WTF(");\n");
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
	char num[42];
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
		compileStoredAss();
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
	WTF("[");
	writeTempVar(randomvar);
	WTF("] != 1) {\n");
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
	char num[42];
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
		compileStoredAss();
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
	WTF("[");
	writeTempVar(randomvar);
	WTF("] != 1) {\n");
	indentDept++;
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
			if (getExpType(p->exp) / 10 == INTEGER_TYPE / 10) {
				writeIndents();
				int expvar = varcnt - 1;
				WTF("char *");
				writeTempVar(varcnt++);
				WTF(" = makeStringFromInteger(");
				writeTempVar(expvar);
				WTF(");\n");
			}
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
	for (int i = 0; i < j; i++) {
		if (kinds[i] / 10 == INTEGER_TYPE / 10) {
			writeIndents();
			WTF("free(");
			writeTempVar(vars[i]);
			WTF(");\n");
		}
	}
	free(vars);
	free(kinds);
}

void compileReadCall(RCall read) {
	for (int i = 0; i < read->numids; i++) {
		int bytes_read = varcnt++;
		int nbytes = varcnt++;
		int chararray = varcnt++;
		
		writeIndents();
		WTF("int ");
		writeTempVar(bytes_read);
		WTF(";\n");
		writeIndents();
		WTF("size_t ");
		writeTempVar(nbytes);
		// NOTE: maximum number length is 1024 character (ie 10^1024)
		WTF(" = 42;\n");
		writeIndents();
		WTF("char *");
		writeTempVar(chararray);
		WTF(";\n");
		
		writeIndents();
		writeTempVar(chararray);
		WTF(" = malloc( (");
		writeTempVar(nbytes);
		WTF(" + 1) * sizeof(char) );\n");
		// TODO perform check?
		
		writeIndents();
		writeTempVar(bytes_read);
		WTF(" = getline(&");
		writeTempVar(chararray);
		WTF(", &");
		writeTempVar(nbytes);
		WTF(", stdin);\n");
		
		//Perform a check
		writeIndents();
		WTF("if (");
		writeTempVar(bytes_read);
		WTF(" <= 0) { printf(\"INPUTERROR\\n\");}\n");
		
		// KILL THE \n ON THE END
		writeIndents();
		writeTempVar(chararray);
		WTF("[strlen(");
		writeTempVar(chararray);
		WTF(")-1] = \'\\0\'; //Kill the eol \n");
		
		if (read->ids[i]->type /10 == INTEGER_TYPE /10) {
			writeIndents();
			WTF("makeIntegerFromString(");
			writeVarRef(read->ids[i]->name);
			WTF(", ");
			writeTempVar(chararray);
			WTF(");\n");
		} else {
			//TODO boolean. Not asked for in the exercise
		}
		writeIndents();
		WTF("free(");
		writeTempVar(chararray);
		WTF(");\n");
	}
}

void compileStatement(Stmnt statement) {
	if (statement->kind != assStmnt) {
		compileStoredAss();
	}
	switch (statement->kind) {
		case decStmnt: compileDec(statement->dec);
			break;
		case assStmnt:
			if (statement->assignment->lineNr == lastline) {
				halfCompileAss(statement->assignment);
			} else {
				lastline = statement->assignment->lineNr;
				// Compile all stored assignments
				compileStoredAss();
				halfCompileAss(statement->assignment);
			}
			//compileAss(statement->assignment);
			break;
		case funcCallStmnt: break; //TODO:
		case procCallStmnt: break; //TODO;
		case readCallStmnt: compileReadCall(statement->rCall);
			break;
		case writeCallStmnt: compileWriteCall(statement->wCall);
			break;
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
	WTF(getCTypeString((parameter->id->type / 10) *10));
	if (parameter->call == byRef) {
		writeVar(parameter->id->name);
	} else {
		WTF("_");
		writeVarRef(parameter->id->name);
		paramsByVal->numParams++;
		if (paramsByVal->numParams == 1) {
			paramsByVal->params = malloc(paramsByVal->numParams * sizeof (Param));
		} else {
			paramsByVal->params = realloc(paramsByVal->params, paramsByVal->numParams * sizeof (Param));
		}
		paramsByVal->params[paramsByVal->numParams - 1] = parameter;
	}
}

void compileCallByValueInit(){
	if(paramsByVal->numParams > 0) WTF("// make copy variables that are called by value\n");
	for (int i = 0; i < paramsByVal->numParams; i++) {
		writeIndents();
		WTF(getCTypeString(paramsByVal->params[i]->id->type / 10 * 10));
		writeVar(paramsByVal->params[i]->id->name);
		WTF(" = malloc(sizeof ( ");
		WTF(getCTypeString(paramsByVal->params[i]->id->type / 10 * 10));
		WTF("));\n");
		writeIndents();
		writeVar(paramsByVal->params[i]->id->name);
		WTF(" = _");
		writeVarRef(paramsByVal->params[i]->id->name);
		WTF(";\n");
	}
}

void compileCallByValueFree(){
	if(paramsByVal->numParams > 0) WTF("// free the copy variables that are called by value\n");
	for (int i = 0; i < paramsByVal->numParams; i++) {
		writeIndents();
		WTF("freeInteger(");
		writeVarRef(paramsByVal->params[i]->id->name);
		WTF(");\n");
		writeIndents();
		WTF("free(");
		writeVarRef(paramsByVal->params[i]->id->name);
		WTF(");\n");
	}
	
}

void compileFunc(FuncDef function) {
	WTF(getCTypeString((function->id->type / 10) *10));
	writeVar(function->id->name);
	WTF("(");
	paramsByVal = malloc(sizeof (struct Params));
	paramsByVal->numParams = 0;
	for (int i = 0; i < function->numParams; i++) {
		if (i != 0) WTF(", ");
		compileParameter(function->params[i]);
	}
	WTF(") {\n");
	indentDept++;
	compileCallByValueInit();
	
	//func body
	writeIndents();
	WTF(getCTypeString((function->id->type / 10) *10));
	writeVar(function->id->name);
	WTF(" = malloc(sizeof ( ");
	WTF(getCTypeString((function->id->type / 10)*10));
	WTF("));\n");

	for (int i = 0; i < function->numStmnts; i++) {
		compileStatement(function->stmnts[i]);
	}
	compileStoredAss();
	compileCallByValueFree();
	writeIndents();
	WTF("return ");
	writeVarRef(function->id->name);
	WTF(";\n");
	indentDept--;
	WTF("}\n");
	if (paramsByVal->numParams > 0) {
		free(paramsByVal->params);
	}
	free(paramsByVal);
}

void compileProc(ProcDef procedure) {
	WTF("void ");
	WTF(procedure->name);
	WTF("(");
	paramsByVal = malloc(sizeof (struct Params));
	paramsByVal->numParams = 0;
	for (int i = 0; i < procedure->numParams; i++) {
		if (i != 0) WTF(", ");
		compileParameter(procedure->params[i]);
	}
	WTF(") {\n");
	indentDept++;
	compileCallByValueInit();

	// procedure body
	for (int i = 0; i < procedure->numStmnts; i++) {
		compileStatement(procedure->stmnts[i]);
	}
	compileStoredAss();
	compileCallByValueFree();

	indentDept--;
	WTF("}\n");
	if (paramsByVal->numParams > 0) {
		free(paramsByVal->params);
	}
	free(paramsByVal);
}

void compileMain(Prog program) {
	WTF("int main(int argc, char **argv){\n");
	indentDept++;

	/* seed the random generator */
	WTF("struct timeval ");
	int timeval = varcnt++;
	writeTempVar(timeval);
	WTF(";\n");
	writeIndents();
	WTF("gettimeofday(&");
	writeTempVar(timeval);
	WTF(", NULL);\n");
	WTF("srand(");
	writeTempVar(timeval);
	WTF(".tv_usec);\n");


	if (program->numConstDefs > 0) WTF("// global constant mallocs, will be init below\n");
	for (int i = 0; i < program->numConstDefs; i++) {
		writeGlobalDecMalloc(program->constDefs[i]);
	}
	if (program->numConstDefs > 0) WTF("\n");
	if (program->numVarDefs > 0) WTF("// global variable mallocs\n");
	for (int i = 0; i < program->numVarDefs; i++) {
		writeGlobalDecMalloc(program->varDefs[i]);
	}
	if (program->numVarDefs > 0) WTF("\n");
	if (program->numConstDefs > 0) WTF("// global constant initializations\n");
	for (int i = 0; i < program->numConstDefs; i++) {
		writeConstantInitialization(program->constDefs[i]);
	}
	if (program->numConstDefs > 0) WTF("\n");
	if (program->numBodyStmnts > 0) WTF("// main body\n");
	paramsByVal = malloc(sizeof (struct Params));
	paramsByVal->numParams = 0;
	// main doesnt have parameters
	for (int i = 0; i < program->numBodyStmnts; i++) {
		compileStatement(program->bodyStmnts[i]);
	}
	compileStoredAss();

	if (paramsByVal->numParams > 0) {
		free(paramsByVal->params);
	}
	free(paramsByVal);
	writeIndents();
	WTF("return EXIT_SUCCESS;\n");
	indentDept--;
	WTF("}\n");
}

void generateCode(Prog program, char *outputfilename) {
	outputfile = fopen(outputfilename, "w");
	lastline = -1;
	numstatements = 0;
	maxstatements = 42;
	stored = malloc(maxstatements * sizeof (Ass));
	tempvars = malloc(maxstatements * sizeof (int));

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

	free(stored);
	free(tempvars);

	fclose(outputfile);
}
